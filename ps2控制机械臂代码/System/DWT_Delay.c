#include "stm32f10x.h"
#include "core_cm3.h"  // CMSIS ͷ�ļ����ṩ DWT �Ĵ�������

#define DWT_CTRL    (*(volatile uint32_t*)0xE0001000)
#define DWT_CYCCNT  (*(volatile uint32_t*)0xE0001004)
#define DEMCR       (*(volatile uint32_t*)0xE000EDFC)
#define DEMCR_TRCENA (1 << 24)

void DWT_Delay_Init(void)
{
    DEMCR |= DEMCR_TRCENA;        // ʹ�� DWT
    DWT_CYCCNT = 0;               // ���������
    DWT_CTRL |= 1;                // ʹ�� cycle counter
}

void DWT_Delay_us(uint32_t us)
{
    uint32_t start = DWT_CYCCNT;
    uint32_t cycles = (SystemCoreClock/1000000) * us;
    while ((DWT_CYCCNT - start) < cycles);
}

void DWT_Delay_ms(uint32_t ms)
{
    uint32_t start = DWT_CYCCNT;
    uint32_t cycles = (SystemCoreClock/1000) * ms;
    while ((DWT_CYCCNT - start) < cycles);
}
