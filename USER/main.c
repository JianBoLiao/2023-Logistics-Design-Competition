#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "control.h"
#include "timer.h"
#include "coco_claw.h"
#include "lock_claw.h"
#include "beep.h"
 

int main(void)
{	 
	delay_init();
	KEY_Init();
	BEEP_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	TIM3_PWM_Init(19999,71);	 //PWMÆµÂÊ=72000000/20000/72=50hz
	canInit();
	uart_init(9600);
	chassisInit(&chassis, 1, 2, 3);
	cocoClawInit(4);
	lockClawInit(5);
	LED_Init();
	long ledCnt = 0;
	while(1){
		if(KEY_Scan(0)) break;
		int obj_id = ledCnt / 250;
		if(obj_id >= 12 && obj_id < 18){
			BEEP = 0;
			LED1 = 1; 
		}else if(obj_id == 18){
			obj_id = 0;
			ledCnt = 0;
		}else if(obj_id % 2 == 1){
			LED1 = 1; 
			BEEP = 0;
		}else if((detect >> (obj_id / 2) & 1) == 0){
			BEEP = 1;
			LED1 = 1;
		} else if((detect >> (obj_id / 2) & 1) == 1){
			BEEP = 0;
			LED1 = 0;
		}
		delay_ms(1);
		ledCnt++;
	}
//	delay_ms(1000);	//waiting for motor
	
	loadInitAngle();
	LED0 = !LED0;
//	control();
	testAll();
	LED0 = !LED0;
	safe();
}



