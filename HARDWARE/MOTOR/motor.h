#ifndef __MOTOR
#define __MOTOR

#include "can.h"

typedef struct Motor{
	int id;
	int16_t	 	speed_rpm;
	long 	angle;				//abs angle range:[0,8191]
	long 	last_angle;	  //abs angle range:[0,8191]
	s16 initAngle;
	long realAngle;
	long signal;
	int orient;
	uint16_t	offset_angle;
	s16       error_sum;
	s16       last_error;
	s16       error_sum_x;
	s16       last_error_x;
	u8 cnt;
	double Kp;
	double Ki;
	double Kd;
	double Kp_x;
	double Ki_x;
	double Kd_x;
}Motor;	

void motorInit(Motor* motor, u8 _id);
void getMotorInfo(Motor* motor);
void setMotorCurrent(long iq, Motor* motor);   //Only used when id 1~4
void run_at_rate(long ideal_rate, Motor* motor);
//void run_to_angle(s16 idealAngle, Motor* motor);
u8 run_to_angle(float idealAngle, Motor* motor);
void loadMotorInitAngle(Motor* motor);

extern Motor motor;
#endif

	