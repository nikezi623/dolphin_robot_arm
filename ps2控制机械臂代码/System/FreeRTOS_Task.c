#include "stm32f10x.h"                  // Device header
#include "FreeRTOS.h"
#include "task.h"
#include "MyPS2.h"
#include "Servo.h"
#include "MySPI.h"
#include "OLED.h"

#define A_Angle_Plus_STACK_SIZE 	256
#define A_Angle_Minus_STACK_SIZE  	256
#define B_Angle_Plus_STACK_SIZE 	256
#define B_Angle_Minus_STACK_SIZE  	256
#define C_Angle_Plus_STACK_SIZE 	256
#define C_Angle_Minus_STACK_SIZE  	256
#define D_Angle_Plus_STACK_SIZE 	256
#define D_Angle_Minus_STACK_SIZE  	256
#define vPs2Task_STACK_SIZE  		256
#define vARMTask_STACK_SIZE  		256
#define InitArm_ByStart_STACK_SIZE  256

#define vPs2Task_PRIORITY  			8
#define vARMTask_PRIORITY  			7
#define InitArm_ByStart_PRIORITY  	6
#define A_Angle_Plus_PRIORITY 		5
#define A_Angle_Minus_PRIORITY  	5
#define B_Angle_Plus_PRIORITY 		5
#define B_Angle_Minus_PRIORITY  	5
#define C_Angle_Plus_PRIORITY 		5
#define C_Angle_Minus_PRIORITY  	5
#define D_Angle_Plus_PRIORITY 		5
#define D_Angle_Minus_PRIORITY  	5

TaskHandle_t A_Angle_Plus_Handler;
TaskHandle_t A_Angle_Minus_Handler;
TaskHandle_t B_Angle_Plus_Handler;
TaskHandle_t B_Angle_Minus_Handler;
TaskHandle_t C_Angle_Plus_Handler;
TaskHandle_t C_Angle_Minus_Handler;
TaskHandle_t D_Angle_Plus_Handler;
TaskHandle_t D_Angle_Minus_Handler;
TaskHandle_t vPs2Task_Handler;
TaskHandle_t vARMTask_Handler;
TaskHandle_t InitArm_ByStart_Handler;

void A_Angle_Plus(void *pvParameters);
void A_Angle_Minus(void *pvParameters);
void B_Angle_Plus(void *pvParameters);
void B_Angle_Minus(void *pvParameters);
void C_Angle_Plus(void *pvParameters);
void C_Angle_Minus(void *pvParameters);
void D_Angle_Plus(void *pvParameters);
void D_Angle_Minus(void *pvParameters);
void vPs2Task(void *pvParameters);
void vARMTask(void *pvParameters);
void InitArm_ByStart(void *pv);

void vStartTask(void *pvParameters)
{	
	taskENTER_CRITICAL();
	xTaskCreate(A_Angle_Plus, "A_Angle_Plus", A_Angle_Plus_STACK_SIZE, NULL, A_Angle_Plus_PRIORITY, &A_Angle_Plus_Handler);
	xTaskCreate(A_Angle_Minus, "A_Angle_Minus", A_Angle_Minus_STACK_SIZE, NULL, A_Angle_Minus_PRIORITY, &A_Angle_Minus_Handler);
	xTaskCreate(B_Angle_Plus, "B_Angle_Plus", B_Angle_Plus_STACK_SIZE, NULL, B_Angle_Plus_PRIORITY, &B_Angle_Plus_Handler);
	xTaskCreate(B_Angle_Minus, "B_Angle_Minus", B_Angle_Minus_STACK_SIZE, NULL, B_Angle_Minus_PRIORITY, &B_Angle_Minus_Handler);
	xTaskCreate(C_Angle_Plus, "C_Angle_Plus", C_Angle_Plus_STACK_SIZE, NULL, C_Angle_Plus_PRIORITY, &C_Angle_Plus_Handler);
	xTaskCreate(C_Angle_Minus, "C_Angle_Minus", C_Angle_Minus_STACK_SIZE, NULL, C_Angle_Minus_PRIORITY, &C_Angle_Minus_Handler);
	xTaskCreate(D_Angle_Plus, "D_Angle_Plus", D_Angle_Plus_STACK_SIZE, NULL, D_Angle_Plus_PRIORITY, &D_Angle_Plus_Handler);
	xTaskCreate(D_Angle_Minus, "D_Angle_Minus", D_Angle_Minus_STACK_SIZE, NULL, D_Angle_Minus_PRIORITY, &D_Angle_Minus_Handler);
	xTaskCreate(vPs2Task, "vPs2Task", vPs2Task_STACK_SIZE, NULL, vPs2Task_PRIORITY, &vPs2Task_Handler);
	xTaskCreate(vARMTask, "vARMTask", vARMTask_STACK_SIZE, NULL, vARMTask_PRIORITY, &vARMTask_Handler);
	xTaskCreate(InitArm_ByStart, "InitArm_ByStart", InitArm_ByStart_STACK_SIZE, NULL, InitArm_ByStart_PRIORITY, &InitArm_ByStart_Handler);
	taskEXIT_CRITICAL();

	vTaskDelete(NULL);		
}

void vPs2Task(void *pvParameters)
{
	while(1)
	{
		Init_MOSI_MISO();

		Get_Message();
		Show_Mode();		
		
		Get_JoyStick(&Lx, &Ly, &Rx, &Ry);
		Show_JoyStick(Lx, Ly, Rx, Ry);
		
		Show_Key();
		vTaskDelay(20);
	}
}

void vARMTask(void *pvParameters)
{
	while(1)
	{
		
		if (Get_Mode() == RED_MODE)
		{
			vTaskResume(A_Angle_Plus_Handler);
			vTaskResume(A_Angle_Minus_Handler);
			vTaskResume(B_Angle_Plus_Handler);
			vTaskResume(B_Angle_Minus_Handler);
			vTaskResume(C_Angle_Plus_Handler);
			vTaskResume(C_Angle_Minus_Handler);
		}

		if (Get_Mode() == GREEN_MODE)
		{
			vTaskSuspend(A_Angle_Plus_Handler);
			vTaskSuspend(A_Angle_Minus_Handler);
			vTaskSuspend(B_Angle_Plus_Handler);
			vTaskSuspend(B_Angle_Minus_Handler);
			vTaskSuspend(C_Angle_Plus_Handler);
			vTaskSuspend(C_Angle_Minus_Handler);
		}
		vTaskDelay(10);
	}
}
