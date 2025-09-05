#ifndef __MyPS2_H
#define __MyPS2_H

void PS2_Init(void);
void Get_Message(void);
uint8_t Get_Mode(void);
void Show_Mode(void);
void Init_MOSI_MISO(void);
void Get_JoyStick(uint8_t *Lx, uint8_t *Ly, uint8_t *Rx, uint8_t *Ry);
void Show_JoyStick(uint8_t Lx, uint8_t Ly, uint8_t Rx, uint8_t Ry);
uint16_t Get_Key(void);
void Show_Key(void);

extern uint8_t MOSI_Data[];
extern uint8_t MISO_Data[];

#endif
