#ifndef __CONTROL
#define __CONTROL

#include "chassis.h"
#include "delay.h"
#include "key.h"

extern u8 detect;

void control(void);
void safe(void);
void getAllMotorInfo(void);
void takeCoca();
void putDownCoca();
void takeLock();
void putDownLock();
void stop(int nms);
void test();
void testHeight();
void testAll();
void testNew();
void testMG();
void takeFirstCoca();
void takeLastLock();
void testCourt();

#endif