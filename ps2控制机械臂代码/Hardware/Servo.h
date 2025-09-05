#ifndef __Servo_H
#define __Servo_H

#define A_ANGLE_INIT_VALUE 		90
#define B_ANGLE_INIT_VALUE 		0
#define C_ANGLE_INIT_VALUE 		180
#define D_ANGLE_INIT_VALUE 		65

#define A_ANGLE_MAX 			180
#define A_ANGLE_MIN 			0

#define B_ANGLE_MAX 			85
#define B_ANGLE_MIN 			0

#define C_ANGLE_MAX 			180
#define C_ANGLE_MIN 			90

#define D_ANGLE_MAX 			114
#define D_ANGLE_MIN 			65

void Servo_Init(void);
void Set_A_Angle(float A_Angle);
void Set_B_Angle(float A_Angle);
void Set_C_Angle(float C_Angle);
void Set_D_Angle(float D_Angle);

extern uint8_t Lx, Ly, Rx, Ry;
extern float A_Angle;
extern float B_Angle;
extern float C_Angle;
extern float D_Angle;

#endif
