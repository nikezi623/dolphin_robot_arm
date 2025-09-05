#include "stm32f10x.h"                  // Device header
#include "MySPI.h"
#include "OLED.h"
#include "Delay.h"
#include "Servo.h"
#include "MySPI.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_Task.h"

uint16_t ID;
uint8_t MOSI_Data[9] = {0x01, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t MISO_Data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void Init_MOSI_MISO(void)
{
	MOSI_Data[0] = 0x01; MOSI_Data[1] = 0x42;
	for (int i = 2; i < 9; i ++) MOSI_Data[i] = 0x00;
	for (int i = 0; i < 9; i ++) MISO_Data[i] = 0x00;
}

void PS2_Init(void)
{
	MySPI_Init();
}

void Get_Message(void) //获取手柄数据
{
	MySPI_Start();
	for (int i = 0; i < 9; i ++)
	{
		MISO_Data[i] = Swap_Bits(MOSI_Data[i]);
	}
	MySPI_Stop();
}

uint8_t Get_Mode(void)
{
	return MISO_Data[1];
}

void Show_Mode(void) //显示红、绿模式
{
	if (Get_Mode() == GREEN_MODE) OLED_ShowString(1, 1, "Green");
	if (Get_Mode() == RED_MODE) OLED_ShowString(1, 1, "Red  ");
}

void Get_JoyStick(uint8_t *Lx, uint8_t *Ly, uint8_t *Rx, uint8_t *Ry)
{
	*Lx = MISO_Data[7]; *Ly = MISO_Data[8];
	*Rx = MISO_Data[5]; *Ry = MISO_Data[6];	
}

void Show_JoyStick(uint8_t Lx, uint8_t Ly, uint8_t Rx, uint8_t Ry)
{
	OLED_ShowHexNum(2, 4, Lx, 3); OLED_ShowHexNum(2, 11, Ly, 3); OLED_ShowHexNum(3, 4, Rx, 3); OLED_ShowHexNum(3, 11, Ry, 3);
}

uint16_t Get_Key(void)
{
	return MISO_Data[3] << 8 | MISO_Data[4];
}

void Show_Key(void)
{
	OLED_ShowHexNum(4, 1, Get_Key(), 4);
}

void InitArm_ByStart(void *pv)
{
	while(1)
	{
		if (Get_Key() == START)
		{
			vTaskSuspend(A_Angle_Plus_Handler);
			vTaskSuspend(A_Angle_Minus_Handler);
			vTaskSuspend(B_Angle_Plus_Handler);
			vTaskSuspend(B_Angle_Minus_Handler);
			vTaskSuspend(C_Angle_Plus_Handler);
			vTaskSuspend(C_Angle_Minus_Handler);
			vTaskSuspend(D_Angle_Plus_Handler);
			vTaskSuspend(D_Angle_Minus_Handler);
			vTaskSuspend(vARMTask_Handler);
			
			Set_A_Angle(A_ANGLE_INIT_VALUE);
			Set_B_Angle(B_ANGLE_INIT_VALUE);
			Set_C_Angle(C_ANGLE_INIT_VALUE);
			Set_D_Angle(D_ANGLE_INIT_VALUE);
			
			A_Angle = A_ANGLE_INIT_VALUE;
			B_Angle = B_ANGLE_INIT_VALUE;
			C_Angle = C_ANGLE_INIT_VALUE;
			D_Angle = D_ANGLE_INIT_VALUE;
		
			vTaskDelay(1000);
			
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
			
			vTaskResume(D_Angle_Plus_Handler);
			vTaskResume(D_Angle_Minus_Handler);
			vTaskResume(vARMTask_Handler);
		}
		vTaskDelay(20);
	}
}
