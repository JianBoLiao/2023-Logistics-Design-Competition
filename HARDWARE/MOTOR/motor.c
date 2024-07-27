#include "motor.h"
#include "string.h"
#include "sys.h"
#include "math.h"
Motor motor;

const float TOL_ERROR_X = 1000;
const float TOL_ERROR_V = 20;
void getMotorInfo(Motor* motor)
{
	u8 bufId =8 * (motor->id - 1);
	motor->angle=(long)(CAN_RX_BUF[0 + bufId]<<8|CAN_RX_BUF[1 + bufId]);
	
	if(motor->angle-motor->last_angle<-6000)
	{
		motor->signal += 1;
	}
	if(motor->angle-motor->last_angle>6000)
	{
		motor->signal -= 1;
	} 
	
	motor->last_angle = motor->angle;
	motor->angle += motor->signal*8191;
	motor->speed_rpm = (s16)(CAN_RX_BUF[2 + bufId]<<8|CAN_RX_BUF[3 + bufId]) * motor->orient;
	//motor->real_current = (u16)(CAN_RX_BUF[4 + bufId]<<8|CAN_RX_BUF[5 + bufId]); // 有什么用？
	//motor->hall = CAN_RX_BUF[6 + bufId];
	motor->realAngle = (motor->angle - motor->initAngle) * motor->orient;
}

void setMotorCurrent(long iq, Motor* motor)
{
	if(iq<-16384) 
		iq=-16384;
	if(iq>16384)
		iq=16384;
	
	int send_id=motor->id;
	CAN_ITConfig(CAN1,CAN_IT_FMP0, DISABLE);
	if(send_id <= 4){
		CAN_TX_BUF1[2*(send_id-1)] = iq>>8;
		CAN_TX_BUF1[2*(send_id-1)+1] = iq;
	}
	else{
		CAN_TX_BUF2[2*(send_id-5)] = iq>>8;
		CAN_TX_BUF2[2*(send_id-5)+1] = iq;
	}
	CAN_ITConfig(CAN1,CAN_IT_FMP0, ENABLE);
}

void run_at_rate(long ideal_rate, struct Motor* motor)
{
	getMotorInfo(motor);
//    if(ideal_rate==0) // 这样会不会导致电机不好锁死？
//    {
//        setMotorCurrent(0, motor);
//    }
	
    long error=ideal_rate-motor->speed_rpm;
    motor->error_sum+=error;
	
	//double Kp_out=motor->Kp*error;
	//double Ki_out=motor->Ki*(motor->error_sum);
	//double Kd_out=motor->Kd*(error-motor->last_error);
	
	float Kp_out=motor->Kp*error;
	float Ki_out=motor->Ki*(motor->error_sum);
	float Kd_out=motor->Kd*(error-motor->last_error);
	
    long iq=(Kp_out+Ki_out+Kd_out) * motor->orient;
    motor->last_error=error;
    setMotorCurrent(iq, motor);
}

u8 run_to_angle(float _idealAngle, Motor* motor){
		long idealAngle=_idealAngle * 19.15 * 8191 / 360;		//_idealAngle:输出端的角度，单位为度
		long error=idealAngle-motor->realAngle;
		motor->error_sum_x += error;
		long rate = motor->Kp_x * error + motor->Kd_x * (error - motor->last_error_x) + motor->Ki_x * motor->error_sum_x;
		run_at_rate(rate, motor);
		motor->last_error_x = error;
		if((fabs(error) < TOL_ERROR_X) && (fabs(motor->speed_rpm) < TOL_ERROR_V)){
			motor->cnt++;	
		}
		else {
			motor->cnt = 0;
		}
		
		if(motor->cnt > 100) {
			motor->cnt = 101;
			return 1;
		}
		
		return 0;
}

void motorInit(Motor* motor, u8 _id){
	motor->id = _id;
	if(motor->id == 1 || motor->id == 2){
		motor->Kp = 5;
		motor->Ki = 0.05;
		motor->Kd = 8;
		motor->Kp_x = 0.06;
		motor->Ki_x = 0;
		motor->Kd_x = 0.008;
	}
	if(motor->id == 3){
		motor->Kp = 20;
		motor->Ki = 0.05;
		motor->Kd = 4;
		motor->Kp_x = 0.15;
		motor->Ki_x = 0.0003;
		motor->Kd_x = 0.01;
	}
	if(motor->id == 4){
		motor->Kp = 15;
		motor->Ki = 0.15;
		motor->Kd = 8;
		motor->Kp_x = 0.2;
		motor->Ki_x = 0;
		motor->Kd_x = 0.008;
	}
	
	if(motor->id == 5){
		motor->Kp = 25;
		motor->Ki = 0.15;
		motor->Kd = 10;
		motor->Kp_x = 0.2;
		motor->Ki_x = 0;
		motor->Kd_x = 0.008;
	}
	if(motor->id == 1) motor->orient = -1;
	if(motor->id == 2) motor->orient = 1;
	if(motor->id == 3) motor->orient = 1;
	if(motor->id == 4) motor->orient = 1;
	if(motor->id == 5) motor->orient = 1;
}

void loadMotorInitAngle(Motor* motor){
	getMotorInfo(motor);
	motor->initAngle = motor->angle;
}
