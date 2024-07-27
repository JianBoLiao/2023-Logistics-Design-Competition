#include "control.h"
u8 detect = 0x15;
const float LOCK_MAX_HEIGHT = 265;
const float COCO_MAX_HEIGHT = 242;
const float COCO1_PUT_DOWN_ANGLE = 40.3266;
const float COCO2_PUT_DOWN_ANGLE = 53.6255;
const float COCO_PUT_DOWN_ANGLE = 46.5;
const float LOCK_PUT_DOWN_ANGLE = 132.0309;
const float COCA_PRE_HEIGHT = 122;
const float COCA_HOLD_HEIGHT = 0.2;
const float COCA_MOVE_HEIGHT = 200;
const float LOCK_PRE_HEIGHT = 160;
const float LOCK_HOLD_HEIGHT = 10;
const float LOCK_MOVE_HEIGHT = 220;
const float A4_HEIGHT = 205;
const float TECANGLE = 88.8;
const float TAKE_SIDE = -1690;
const float PUT_SIDE = 480;
void takeLastLock(){
	while(!lockMovetoHeight(LOCK_MOVE_HEIGHT,LOCK_PRE_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		delay_ms(1);
	}
	lockRelease();
	while(!lockMovetoHeight(LOCK_PRE_HEIGHT, LOCK_HOLD_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		delay_ms(1);
	}
	lockHold();
	stop(500);
}

void takeFirstCoca(){
	while(!cocoMovetoHeight(COCA_MOVE_HEIGHT, COCA_HOLD_HEIGHT)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	cocoHold();
	stop(500);
}
void takeCoca(){
	while(!cocoMovetoHeight(COCA_MOVE_HEIGHT, COCA_PRE_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	cocoProtect();
	stop(1000);
	cocoPrepare();
	stop(500);
	while(!cocoMovetoHeight(COCA_PRE_HEIGHT, COCA_HOLD_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	cocoHold();
	stop(500);
	
	
}

void takeLastCoca(){
	while(!cocoMovetoHeight(COCA_MOVE_HEIGHT, COCA_PRE_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	cocoProtect();
	stop(1000);
	cocoPrepare();
	stop(200);
	cocoBack();
	stop(1000);
	cocoPrepare();
	stop(500);
	while(!cocoMovetoHeight(COCA_PRE_HEIGHT, COCA_HOLD_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	cocoHold();
	stop(500);
}
void putDownCoca(){
	stop(500);
	while(!cocoMovetoHeight(COCO_MAX_HEIGHT, A4_HEIGHT + COCA_HOLD_HEIGHT - 1))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	cocoProtect();
	stop(1000);
	cocoRelease();
	stop(500);
}


void takeLock(){
	while(!lockMovetoHeight(LOCK_MOVE_HEIGHT,LOCK_PRE_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		delay_ms(1);
	}
	lockRelease();
	while(!lockMovetoHeight(LOCK_PRE_HEIGHT, LOCK_HOLD_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		delay_ms(1);
	}
	lockHold();
	stop(500);
	while(!lockMovetoHeight(LOCK_HOLD_HEIGHT, LOCK_MOVE_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		delay_ms(1);
	}
}

void putDownLock(){
	while(!lockMovetoHeight(LOCK_MAX_HEIGHT, LOCK_MAX_HEIGHT))
	{
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		delay_ms(1);
	}
	stop(500);
	lockRelease();
}
/* void control(void){

	
	u8 signal1 = 0;
	u8 signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(200);
		signal2 = lockMovetoHeight(200);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}
	
	while(!chassisSpinToAngle(&chassis, TECANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
	}
	
	while(!chassisMoveToPos(&chassis, TAKE_SIDE)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	for(int i = 0; i < 500; i++){
		chassisMoveAtSpeed(&chassis, -80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}

	//obj数组指示物品的摆放，定义0为乐扣，1为可乐
	u8 obj[6];
	float angleOfCola[3];
	float angleOfLock[3];
	u8 cocaCnt = 0;
	int j = 0, k = 0;
	for(int i = 0; i < 6; i++){
		obj[i] = (detect >> i) & 1;
	}
	for(int i = 0; i < 6; i++){
		if(obj[i] == 1){
			angleOfCola[j] = 36.0 * i;
			j++;
		}else{
			angleOfLock[k] = 36.0 * i;
			k++;
		}
	}
	
	
	for(int i = 0; i < 2; i++){
		while(!chassisSpinToAngle(&chassis, angleOfCola[i] + TECANGLE)){
			run_at_rate(0, &chassis.motor[0]);
			run_at_rate(0, &chassis.motor[1]);
			run_at_rate(0, &cocoClaw.motor);
			run_at_rate(0, &lockClaw.motor);
			delay_ms(1);
		}
		
		//如果该物品为可乐
		takeCoca();
	}
	
	while(!chassisSpinToAngle(&chassis, TECANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
	}
	
	while(!chassisMoveToPos(&chassis, PUT_SIDE)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	for(int i = 0; i < 600; i++){
		chassisMoveAtSpeed(&chassis, 80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	signal1 = 0;
	signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(COCO_MAX_HEIGHT);
		signal2 = lockMovetoHeight(LOCK_MAX_HEIGHT);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}
	
	while(!chassisSpinToAngle(&chassis, COCO1_PUT_DOWN_ANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
	}
	putDownCoca();
	
	while(!chassisMoveToPos(&chassis, 0)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	while(!chassisSpinToAngle(&chassis, TECANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
	}
	
	while(!chassisMoveToPos(&chassis, TAKE_SIDE)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	for(int i = 0; i < 500; i++){
		chassisMoveAtSpeed(&chassis, -80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	while(!chassisSpinToAngle(&chassis, angleOfCola[2] + TECANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	takeCoca();
	
	for(int i = 0; i < 3; i++){
		while(!chassisSpinToAngle(&chassis, angleOfLock[i] + 180 + TECANGLE)){
			run_at_rate(0, &chassis.motor[0]);
			run_at_rate(0, &chassis.motor[1]);
			run_at_rate(0, &cocoClaw.motor);
			run_at_rate(0, &lockClaw.motor);
			delay_ms(1);
		}
		takeLock();
	}
	
	while(!chassisSpinToAngle(&chassis, 360 + TECANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}

	while(!chassisMoveToPos(&chassis, PUT_SIDE)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	for(int i = 0; i < 600; i++){
		chassisMoveAtSpeed(&chassis, 80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	signal1 = 0;
	signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(COCO_MAX_HEIGHT);
		signal2 = lockMovetoHeight(LOCK_MAX_HEIGHT);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}

	while(!chassisSpinToAngle(&chassis, 360 + COCO2_PUT_DOWN_ANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
	}
	
	putDownCoca();	
	
	while(!chassisMoveToPos(&chassis, 0)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	while(!chassisSpinToAngle(&chassis, 360 + TECANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}

	while(!chassisMoveToPos(&chassis, PUT_SIDE)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	for(int i = 0; i < 600; i++){
		chassisMoveAtSpeed(&chassis, 80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	while(!chassisSpinToAngle(&chassis, 360 + LOCK_PUT_DOWN_ANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
	}
	
	putDownLock();
}
*/
void safe(void){
	cocoRelease();
	lockRelease();
	while(1){
		stop(1);
	}
}

void getAllMotorInfo(void){
	for(int i = 0; i < 3; i++){
		getMotorInfo(&chassis.motor[i]);
	}
	getMotorInfo(&cocoClaw.motor);
	getMotorInfo(&lockClaw.motor);
}

void stop(int nms){
	for(int i = 0; i < nms; i++){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
}

/*
void test(){
	u8 signal1 = 0;
	u8 signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(200);
		signal2 = lockMovetoHeight(200);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}
	while(!chassisMoveToPos(&chassis, 500)){
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
}

void testHeight(){
	u8 signal1 = 0;
	u8 signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(COCO_MAX_HEIGHT);
		signal2 = lockMovetoHeight(LOCK_MAX_HEIGHT);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}
	
}
*/
void testAll(){
	u8 signal1 = 0;
	u8 signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(0, 200);
		signal2 = lockMovetoHeight(0, 200);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}
	
	signal1 = 0;
	signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = chassisMoveToPos(&chassis, 0, TAKE_SIDE);
		signal2 = chassisSpinToAngle(&chassis, 0, TECANGLE);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	for(int i = 0; i < 500; i++){
		chassisMoveAtSpeed(&chassis, -80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	cocoPrepare();
	//obj数组指示物品的摆放，定义0为乐扣，1为可乐
	u8 obj[6];
	float angleOfCola[3];
	float angleOfLock[3];
	u8 cocaCnt = 0;
	int j = 0, k = 0;
	for(int i = 0; i < 6; i++){
		obj[i] = (detect >> i) & 1;
	}
	for(int i = 0; i < 6; i++){
		if(obj[i] == 1){
			angleOfCola[j] = 36.0 * i;
			j++;
		}else{
			angleOfLock[k] = 36.0 * i;
			k++;
		}
	}
	
	for(int i = 0; i < 3; i++){
		if(i == 0){
			while(!chassisSpinToAngle(&chassis, TECANGLE, angleOfCola[i] + TECANGLE)){
				run_at_rate(0, &chassis.motor[0]);
				run_at_rate(0, &chassis.motor[1]);
				run_at_rate(0, &cocoClaw.motor);
				run_at_rate(0, &lockClaw.motor);
				delay_ms(1);
			}
			takeFirstCoca();
		}
		//如果该物品为可乐
		else if(i == 1){
			signal1 = 0;
			signal2 = 0;
			while(!signal1 || !signal2){
				signal1 = chassisSpinToAngle(&chassis, angleOfCola[i - 1] + TECANGLE, angleOfCola[i] + TECANGLE);
				signal2 = cocoMovetoHeight(COCA_HOLD_HEIGHT, COCA_MOVE_HEIGHT);
				run_at_rate(0, &chassis.motor[0]);
				run_at_rate(0, &chassis.motor[1]);
				run_at_rate(0, &lockClaw.motor);
				delay_ms(1);
			}
			takeCoca();
		}
		
		else {
			signal1 = 0;
			signal2 = 0;
			while(!signal1 || !signal2){
				signal1 = chassisSpinToAngle(&chassis, angleOfCola[i - 1] + TECANGLE, angleOfCola[i] + TECANGLE);
				signal2 = cocoMovetoHeight(COCA_HOLD_HEIGHT, COCA_MOVE_HEIGHT);
				run_at_rate(0, &chassis.motor[0]);
				run_at_rate(0, &chassis.motor[1]);
				run_at_rate(0, &lockClaw.motor);
				delay_ms(1);
			}
			takeLastCoca();
		}
		
	}
	
	for(int i = 0; i < 3; i++){
		if(i == 0){
			signal1 = 0;
			signal2 = 0;
			while(!signal1 || !signal2){
				signal1 = chassisSpinToAngle(&chassis, TECANGLE + angleOfCola[2], angleOfLock[i] + 180 + TECANGLE);
				signal2 = cocoMovetoHeight(COCA_HOLD_HEIGHT, COCA_MOVE_HEIGHT);
				run_at_rate(0, &chassis.motor[0]);
				run_at_rate(0, &chassis.motor[1]);
				run_at_rate(0, &lockClaw.motor);
				delay_ms(1);
			}
			takeLock();
		}
		
		else {
			while(!chassisSpinToAngle(&chassis, angleOfLock[i - 1] + 180 + TECANGLE, angleOfLock[i] + 180 + TECANGLE)){
				run_at_rate(0, &chassis.motor[0]);
				run_at_rate(0, &chassis.motor[1]);
				run_at_rate(0, &cocoClaw.motor);
				run_at_rate(0, &lockClaw.motor);
				delay_ms(1);
			}
			takeLock();
		}
	}
	
	signal1 = 0;
	signal2 = 0;
	u8 signal3 = 0;
	u8 signal4 = 0;
	while(!signal1 || !signal2 || !signal3 || !signal4){
		signal1 = chassisSpinToAngle(&chassis, angleOfLock[2] + 180 + TECANGLE, 360 + COCO_PUT_DOWN_ANGLE);
		signal2 = chassisMoveToPos(&chassis,TAKE_SIDE, PUT_SIDE);
		signal3 = cocoMovetoHeight(COCA_MOVE_HEIGHT, COCO_MAX_HEIGHT);
		signal4 = lockMovetoHeight(LOCK_MOVE_HEIGHT, LOCK_MAX_HEIGHT);
		delay_ms(1);
	}

	
	for(int i = 0; i < 500; i++){
		chassisMoveAtSpeed(&chassis, 80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	putDownCoca();	
	
	while(!chassisSpinToAngle(&chassis, 360 + COCO_PUT_DOWN_ANGLE, 360 + LOCK_PUT_DOWN_ANGLE)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	putDownLock();
	
	signal1 = 0;
	signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = chassisMoveToPos(&chassis, PUT_SIDE, PUT_SIDE - 20);
		signal2 = chassisSpinToAngle(&chassis, 360 + LOCK_PUT_DOWN_ANGLE, 360 + LOCK_PUT_DOWN_ANGLE + 3);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
}


void testNew(){
	u8 signal1 = 0;
	u8 signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(0, 200);
		signal2 = lockMovetoHeight(0, 200);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}
	
	while(!chassisSpinToAngle(&chassis, 0, 90)){
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
}

void testMG(){
	cocoHold();
	stop(1000);
	cocoProtect();
	stop(1000);
	cocoPrepare();
	stop(1000);
	cocoHold();
	stop(1000);
}

void testCourt(){
	u8 signal1 = 0;
	u8 signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = cocoMovetoHeight(0, 200);
		signal2 = lockMovetoHeight(0, 200);
		run_at_rate(0, &chassis.motor[0]);
		run_at_rate(0, &chassis.motor[1]);
		run_at_rate(0, &chassis.motor[2]);
		delay_ms(1);
	}
	
	signal1 = 0;
	signal2 = 0;
	while(!signal1 || !signal2){
		signal1 = chassisMoveToPos(&chassis, 0, TAKE_SIDE);
		signal2 = chassisSpinToAngle(&chassis, 0, TECANGLE);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	for(int i = 0; i < 500; i++){
		chassisMoveAtSpeed(&chassis, -80);
		run_at_rate(0, &chassis.motor[2]);
		run_at_rate(0, &cocoClaw.motor);
		run_at_rate(0, &lockClaw.motor);
		delay_ms(1);
	}
	
	cocoPrepare();
	
	for(int i = 0; i < 6; i++){
		if(i == 0){
			takeFirstCoca();
		}
		else{
			u8 signal1 = 0;
			u8 signal2 = 0;
			while(!signal1 || !signal2){
				signal1 = chassisSpinToAngle(&chassis, TECANGLE + 36 * (i - 1), TECANGLE + 36 * i);
				signal2 = cocoMovetoHeight(COCA_HOLD_HEIGHT, COCA_MOVE_HEIGHT);
				run_at_rate(0, &chassis.motor[0]);
				run_at_rate(0, &chassis.motor[1]);
				run_at_rate(0, &lockClaw.motor);
				delay_ms(1);
			}
			takeCoca();
		}
		while(1){
			if(KEY_Scan(0)) break;
			stop(1);
			
			
		}
	}
}