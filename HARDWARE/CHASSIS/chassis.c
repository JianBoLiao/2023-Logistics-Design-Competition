#include "chassis.h"
const float PI = 3.14159;
const float R = 35.7;
const float REDUCTION_RATIO = 3581.0 / 187.0;	//输出端和转子端之间的减速比
const float K = 8191.0 / 360.0;		//转子端编码器和实际转动角度之间的比值
const float RUN_TO_POS_SPEED = 500;
const float CRITICAL_DISTANCE = 75;		//临界距离,小于这个值时使用位置环
const float GEAR_RATIO = 5.2854;
const float CRITICAL_ANGLE = 2;
const float SPIN_TO_ANGLE_RPM = 6;

const float CHASSIS_LOW_V = 300;
const float CHASSIS_HIGH_V = 1000;
const float CHASSIS_A = 800;

const float CHASSIS_SPIN_LOW_V = 30;
const float CHASSIS_SPIN_HIGH_V = 60;
const float CHASSIS_SPIN_A = 90;
Chassis chassis;
void chassisInit(Chassis* chassis, u8 id1, u8 id2, u8 id3){
	motorInit(&(chassis->motor[0]), id1);
	motorInit(&(chassis->motor[1]), id2);
	motorInit(&(chassis->motor[2]), id3);
	
	chassis->sp_move.low_v = CHASSIS_LOW_V;
	chassis->sp_move.high_v = CHASSIS_HIGH_V;
	chassis->sp_move.acc = CHASSIS_A;
	
	chassis->sp_spin.acc = CHASSIS_SPIN_A;
	chassis->sp_spin.high_v = CHASSIS_SPIN_HIGH_V;
	chassis->sp_spin.low_v = CHASSIS_SPIN_LOW_V;
}

//speed:底盘移动的速度，往a4纸方向是正方向，单位：mm/s
void chassisMoveAtSpeed(Chassis* chassis, float speed){
	float rpm = speed / (2 * PI * R) * 60 * REDUCTION_RATIO;	//round per minute
	run_at_rate(rpm, &chassis->motor[0]);
	run_at_rate(rpm, &chassis->motor[1]);
}

//pos:底盘目标位置， 单位：mm
u8 chassisMoveToPos(Chassis* chassis, float startPos, float endPos){
	long rawAngle = (chassis->motor[0].realAngle + chassis->motor[1].realAngle) / 2;
	float nowAngle = (float)rawAngle / K / REDUCTION_RATIO;
	chassis->nowPos = nowAngle / 360 * 2 * PI * R;
	
	if(( chassis->nowPos < endPos - CRITICAL_DISTANCE ) || 
		( chassis->nowPos > endPos + CRITICAL_DISTANCE )){
		chassisMoveAtSpeed(
			chassis, 
			x_to_v(chassis->nowPos, startPos, endPos, &(chassis->sp_move)) 
		);
		chassis->timeCnt = 0;
	}
	else{
		float angle = endPos / (2 * PI * R) * 360;
		int signal1 = run_to_angle(angle, &chassis->motor[0]);
		int signal2 = run_to_angle(angle, &chassis->motor[1]);
		if (signal1 || signal2) {
			chassis->timeCnt = 0;
			return 1;
		}
	}
	chassis->timeCnt++;
	if(chassis->timeCnt > 5000){
		chassis->timeCnt = 5001;
		return 1;
	}
	return 0;
}

void getChassisInfo(Chassis* chassis){
	getMotorInfo(&chassis->motor[0]);
	getMotorInfo(&chassis->motor[1]);
	getMotorInfo(&chassis->motor[2]);
}

void loadInitAngle(void){
	loadMotorInitAngle(&chassis.motor[0]);
	loadMotorInitAngle(&chassis.motor[1]);
	loadMotorInitAngle(&chassis.motor[2]);
	loadMotorInitAngle(&(cocoClaw.motor));
	loadMotorInitAngle(&(lockClaw.motor));
}

//rpm:转轴大齿轮的rpm,round per minute
void chassisSpinAtRpm(Chassis* chassis, float rpm){
	long rotorEndRpm = rpm * GEAR_RATIO * REDUCTION_RATIO;
	run_at_rate(rotorEndRpm, &chassis->motor[2]);
}

//angle:转轴大齿轮的角度，单位为度
u8 chassisSpinToAngle(Chassis* chassis, float startAngle, float endAngle){
	chassis->nowAngle = (float)chassis->motor[2].realAngle / K / REDUCTION_RATIO / GEAR_RATIO;
	if(chassis->nowAngle < endAngle - CRITICAL_ANGLE || chassis->nowAngle > endAngle + CRITICAL_ANGLE){
		chassisSpinAtRpm(chassis, x_to_v(chassis->nowAngle, startAngle, endAngle, &(chassis->sp_spin)) / 6.0);
	}
	else{
		float rotorAngle = endAngle * GEAR_RATIO;
		int signal = run_to_angle(rotorAngle, &chassis->motor[2]);
		if(signal) {
			chassis->spinTimeCnt = 0;
			return 1;
		}
		
		chassis->spinTimeCnt++;
		if(chassis->spinTimeCnt > 5000){
			chassis->spinTimeCnt = 0;
			return 1;
		}
	}
	
	return 0;
}


