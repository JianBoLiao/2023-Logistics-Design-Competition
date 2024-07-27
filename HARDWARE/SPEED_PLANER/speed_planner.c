#include "speed_planner.h"
#include <math.h>

float x_to_v(float x, float startX, float endX, SpeedPlanner *sp){
	float v_acc, v_uni, v_dec, v;
    if(startX <= endX){
		v_acc = sqrt(2 * sp->acc * (x - startX) + sp->low_v * sp->low_v);
		v_uni = sp->high_v;
		v_dec = sqrt(2 * -sp->acc * (x - endX) + sp->low_v * sp->low_v);
		
		if(x < startX){
			v = sp->low_v;
		}
		else if(x >= startX && x <= endX){
			v = fmin(v_acc, fmin(v_uni, v_dec));
		}
        else{
            v = -sp->low_v;
		}
	}
	else{
		v_acc = -sqrt(2 * -sp->acc * (x - startX) + sp->low_v * sp->low_v);
		v_uni = -sp->high_v;
		v_dec = -sqrt(2 * sp->acc * (x - endX) + sp->low_v * sp->low_v);
		
		if(x > startX){
			v = -sp->low_v;
		}
		else if(x <= startX && x >= endX){
			v = fmax(v_acc, fmax(v_uni, v_dec));
		}
        else{
            v = sp->low_v;
		}
	}
	return v;
}
