#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "MySPI.h"
#include "MyPS2.h"
#include "OLED.h"
#include "Servo.h"

int main(void)
{	
	PS2_Init();
	OLED_Init();
	Servo_Init();
	
	Wait_Connect();

	OLED_ShowString(2, 1, "Lx:000"); OLED_ShowString(2, 8, "Ly:000"); OLED_ShowString(3, 1, "Rx:000"); OLED_ShowString(3, 8, "Ry:000");
	
	while(1)
	{
		Get_Message();
		Show_Mode();
		
		InitArm_ByStart();
		
		Get_JoyStick(&Lx, &Ly, &Rx, &Ry);
		Show_JoyStick(Lx, Ly, Rx, Ry);
		
		Show_Key();
		
		if (Get_Mode() == RED_MODE)
		{
			A_Angle_Plus();
			A_Angle_Minus();
			
			B_Angle_Plus();
			B_Angle_Minus();
			
			C_Angle_Plus();
			C_Angle_Minus();
		}
		
		if (Get_Mode() == GREEN_MODE)
		{
			D_Angle_Plus();
			D_Angle_Minus();

		}
		
		Init_MOSI_MISO();
		Wait_Connect();
	}
}

