#include "coco_claw.h"

CocoClaw cocoClaw;
const float _GEAR_R = 25;
const float _CRITICAL_HEIGHT = 5;
const float _MOVE_SPEED = 50;
const float __PI = 3.14159;
const float __REDUCTION_RATIO = 3581.0 / 187.0;	//Êä³ö¶ËºÍ×ª×Ó¶ËÖ®¼äµÄ¼õËÙ±È
const float __K = 8191.0 / 360.0;		//×ª×Ó¶Ë±àÂëÆ÷ºÍÊµ¼Ê×ª¶¯½Ç¶ÈÖ®¼äµÄ±ÈÖ
const float PRE_HEIGHT = 130;
const float COCA_ACC = 650;
const float COCA_HIGH_V = 450;
const float COCA_LOW_V = 250;

void cocoClawInit(u8 id){
	motorInit(&cocoClaw.motor, id);
	TIM_SetCompare2(TIM3, 19100);
	cocoClaw.nowPwmval = 19100;
	cocoClaw.sp.acc = COCA_ACC;
	cocoClaw.sp.high_v = COCA_HIGH_V;
	cocoClaw.sp.low_v = COCA_LOW_V;
}

void cocoMoveAtSpeed(float speed){
	float rpm = speed / (2 * __PI * _GEAR_R) * 60 * __REDUCTION_RATIO;
	run_at_rate(rpm, &cocoClaw.motor);
}

u8 cocoMovetoHeight(float startHeight, float endHeight){
	float angle = endHeight / _GEAR_R / 2 / __PI * 360;
	float nowHeight = cocoClaw.motor.realAngle / __K / __REDUCTION_RATIO / 360 * 2 * __PI * _GEAR_R;
	
	if((nowHeight < endHeight - _CRITICAL_HEIGHT) || (nowHeight > endHeight + _CRITICAL_HEIGHT)){
		cocoMoveAtSpeed(x_to_v(nowHeight, startHeight, endHeight, &cocoClaw.sp));
	}
	else{
		u8 signal = run_to_angle(angle, &cocoClaw.motor);
		if(signal) {
			cocoClaw.timeCnt = 0;
			return 1;
		}
	}
	
	cocoClaw.timeCnt++;
	if(cocoClaw.timeCnt > 5000){
		cocoClaw.timeCnt = 0;
		return 1;
	}
	return 0;
}

void setPwmval(int pwmval){
	TIM_SetCompare2(TIM3, pwmval);
}
void cocoProtect(){
	setPwmval(17895);
}

void cocoPrepare(){
	setPwmval(18195);
}

void cocoRelease(){
	setPwmval(18695);
}

void cocoHold(){
	setPwmval(17775);
}

void cocoBack(){
	setPwmval(17850);
}
