#ifndef __COCO_CLAW
#define __COCO_CLAW
#include "motor.h"
#include "timer.h"
#include "delay.h"
#include "speed_planner.h"

typedef struct CocoClaw{
	Motor motor;
	int nowPwmval;
	SpeedPlanner sp;
	int timeCnt;
}CocoClaw;

extern CocoClaw cocoClaw;

void cocoClawInit(u8 id);
void cocoMoveAtSpeed(float speed);
u8 cocoMovetoHeight(float startHeight, float endHeight);
void setPwmval(int pwmval);
void cocoPrepare();
void cocoRelease();
void cocoHold();
void cocoProtect();
void cocoBack();
#endif