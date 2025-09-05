#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "MySPI.h"
#include "MyPS2.h"
#include "OLED.h"
#include "Servo.h"
#include "FreeRTOS.h"
#include "task.h"

#define vStartTask_STACK_SIZE 256
#define vStartTask_PRIORITY 1
void vStartTask(void *pvParameters);

int main(void)
{	
	PS2_Init();
	OLED_Init();
	Servo_Init();
	
	Set_A_Angle(A_ANGLE_INIT_VALUE);
	Set_B_Angle(B_ANGLE_INIT_VALUE);
	Set_C_Angle(C_ANGLE_INIT_VALUE);
	Set_D_Angle(D_ANGLE_INIT_VALUE);
	
	Delay_ms(1000);
	
	OLED_ShowString(2, 1, "Lx:000"); OLED_ShowString(2, 8, "Ly:000"); 
	OLED_ShowString(3, 1, "Rx:000"); OLED_ShowString(3, 8, "Ry:000");
	
	xTaskCreate(vStartTask, "vStartTask", vStartTask_STACK_SIZE, NULL, vStartTask_PRIORITY, NULL);
	
	vTaskStartScheduler();
	
	while(1)
	{
		
	}
}

