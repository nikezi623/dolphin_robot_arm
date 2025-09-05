#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "string.h"
#include "MyPS2.h"
#include "Delay.h"
#include "MyPS2.h"
#include "MySPI.h"
#include "FreeRTOS.h"
#include "task.h"
#include "OLED.h"
#include "Servo.h"

uint8_t Lx, Ly, Rx, Ry;
float A_Angle = A_ANGLE_INIT_VALUE;
float B_Angle = B_ANGLE_INIT_VALUE;
float C_Angle = C_ANGLE_INIT_VALUE;
float D_Angle = D_ANGLE_INIT_VALUE;

void Servo_Init(void)
{
	PWM_Init();
}

void Set_A_Angle(float A_Angle)
{
	PWM_SetCompare2A((A_Angle / 1800 + 0.025) * 20000);
}

void Set_B_Angle(float B_Angle)
{
	PWM_SetCompare2B((B_Angle / 1800 + 0.025) * 20000);
}

void Set_C_Angle(float C_Angle)
{
	PWM_SetCompare3C((C_Angle / 1800 + 0.025) * 20000);
}

void Set_D_Angle(float D_Angle)
{
	PWM_SetCompare4D((D_Angle / 1800 + 0.025) * 20000);
}

void A_Angle_Plus(void *pvParameters)
{
	while (1)
	{
		if (Lx < 0x80)
		{
			if (A_Angle < A_ANGLE_MAX) A_Angle += 0.3;
			if (A_Angle > A_ANGLE_MAX) A_Angle = A_ANGLE_MAX;
			Set_A_Angle(A_Angle);
		}
		vTaskDelay(10);
	}
}

void A_Angle_Minus(void *pvParameters)
{	
	while (1)
	{
		if (Lx > 0x80)
		{
			if (A_Angle > A_ANGLE_MIN) A_Angle -= 0.3;
			if (A_Angle < A_ANGLE_MIN) A_Angle = A_ANGLE_MIN;
			Set_A_Angle(A_Angle);
		}
		vTaskDelay(10);
	}
}

void B_Angle_Plus(void *pvParameters)
{
	while (1)
	{
		if(Rx < 0x80)
		{
			if (B_Angle < B_ANGLE_MAX) B_Angle += 0.2;
			if (B_Angle > B_ANGLE_MAX) B_Angle = B_ANGLE_MAX;
			Set_B_Angle(B_Angle);
		}
		vTaskDelay(10);
	}
}

void B_Angle_Minus(void *pvParameters)
{	
	while (1)
	{
		if (Rx > 0x80)
		{
			if (B_Angle > B_ANGLE_MIN) B_Angle -= 0.2;
			if (B_Angle < B_ANGLE_MIN) B_Angle = B_ANGLE_MIN;
			Set_B_Angle(B_Angle);
		}
		vTaskDelay(10);
	}
}

void C_Angle_Plus(void *pvParameters)
{
	while (1)
	{
		if (Ry < 0x7F)
		{
			if (C_Angle < C_ANGLE_MAX) C_Angle += 0.2;
			if (C_Angle > C_ANGLE_MAX) C_Angle = C_ANGLE_MAX;
			Set_C_Angle(C_Angle);
		}
		vTaskDelay(10);
	}
}

void C_Angle_Minus(void *pvParameters)
{	
	while (1)
	{
		if (Ry > 0x7F)
		{
			if (C_Angle > C_ANGLE_MIN) C_Angle -= 0.2;
			if (C_Angle < C_ANGLE_MIN) C_Angle = C_ANGLE_MIN;
			Set_C_Angle(C_Angle);
		}
		vTaskDelay(10);
	}
}

void D_Angle_Plus(void *pvParameters)
{
	while (1)
	{
		if (Get_Key() == L1)
		{
			if (D_Angle < D_ANGLE_MAX) D_Angle += 0.2;
			if (D_Angle > D_ANGLE_MAX) D_Angle = D_ANGLE_MAX;
			Set_D_Angle(D_Angle);
		}
		vTaskDelay(2);
	}
}

void D_Angle_Minus(void *pvParameters)
{	
	while (1)
	{
		if (Get_Key() == R1)
		{
			if (D_Angle > D_ANGLE_MIN) D_Angle -= 0.2;
			if (D_Angle < D_ANGLE_MIN) D_Angle = D_ANGLE_MIN;
			Set_D_Angle(D_Angle);
		}
		vTaskDelay(2);
	}
}
