#ifndef __LOCK_CLAW
#define __LOCK_CLAW
#include "chassis.h"
#include "speed_planner.h"
typedef struct LockClaw{
	Motor motor;
	SpeedPlanner sp;
	int timeCnt;
}LockClaw;

extern LockClaw lockClaw;

void lockClawInit(u8 id);
void lockMoveAtSpeed(float speed);
u8 lockMovetoHeight(float startHeight, float endHeight);
void lockHold();
void lockRelease();
#endif