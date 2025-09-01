#include "stm32f10x.h"                  // Device header
#include "Delay.h"

void MySPI_W_SS(uint16_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_4, (BitAction)BitVal);
}

void MySPI_W_SCLK(uint16_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, (BitAction)BitVal);
}

void MySPI_W_MOSI(uint16_t BitVal)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_7, (BitAction)BitVal);
}

uint8_t MySPI_R_MISO(void)
{
	return GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_6);
}

void MySPI_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	MySPI_W_SS(1);
	MySPI_W_SCLK(1);
}



void MySPI_Start(void)
{
	MySPI_W_SS(0);
}

void MySPI_Stop(void)
{
	MySPI_W_SS(1);
}

uint8_t Swap_Bits(uint8_t SendBits)
{
	uint8_t i, RecieveData = 0x00;
	for (i = 0; i < 8; i ++)
	{
		MySPI_W_MOSI(SendBits & (0x01 << i));
		
		Delay_ms(1);
		
		MySPI_W_SCLK(0);
		if (MySPI_R_MISO() == 1)
		{
			RecieveData |= 0x01 << i;
		}
		
		Delay_ms(1);
		
		MySPI_W_SCLK(1);
		
		Delay_ms(1);
	}
	
	return RecieveData;
}
