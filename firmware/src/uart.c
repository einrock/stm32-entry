#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

#define SYS_CLOCK	(72000000)

int fputc(int c, FILE * fp)
{
	while ((USART1->SR & (0x1 << 7))==0); 
	USART1->DR = (uint8_t)c;
	return c;
}

void uart_init()
{
	// enable port-a, uart
	RCC->APB2ENR = RCC->APB2ENR | (0x1<<14) | (0x1<<2);

	// PA9 --> uart-tx
	GPIOA->CRH = (GPIOA->CRH & ~ (0xF<<4)) | (0xB<<4);

	// baud rate
	USART1->BRR = SYS_CLOCK / 115200;

	// TE, UART Enable
	USART1->CR1 = USART1->CR1 | (0x1<<13) | (0x1<<3);
}

