#ifndef MySPI__H_
#define MySPI__H_

void MySPI_Init(void);
void MySPI_Start(void);
void MySPI_Stop(void);
uint8_t Swap_Bits(uint8_t SendBits);

#define EXDATA 		0xFF
#define GREEN_MODE 	0x41
#define RED_MODE 	0x73
#define LEFT        0x7FFF
#define DOWN        0xBFFF
#define RIGHT       0xDFFF
#define UP          0xEFFF
#define START       0xF7FF
#define R3          0xFBFF
#define L3          0xFDFF
#define SELECT      0xFEFF
#define SQUARE      0xFF7F
#define CROSS       0xFFBF
#define CIRCLE      0xFFDF
#define TRIANGLE    0xFFEF
#define R1          0xFFF7
#define L1          0xFFFB
#define R2          0xFFFD
#define L2          0xFFFE
#endif
