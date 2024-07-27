#ifndef __SPEED_PLANNER
#define __SPEED_PLANNER

typedef struct _SpeedPlanner{
	float acc;
	float low_v;
	float high_v;
}SpeedPlanner;

float x_to_v(float x, float startX, float endX, SpeedPlanner *sp);

#endif