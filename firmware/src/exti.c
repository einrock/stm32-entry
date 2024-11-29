#include "stm32f10x.h"
#include "exti.h"

#ifndef configMAX_SYSCALL_INTERRUPT_PRIORITY
	#define configMAX_SYSCALL_INTERRUPT_PRIORITY (0xbf)
#endif

void exti_init()
{
	/*
	 * enable clock for port-b, port-a, afio ip
	 */
	RCC->APB2ENR = RCC->APB2ENR | (0x1 << 2) | (0x1 << 0);
	
	/*
	 * priority of irq6, irq7
	 */
	*(unsigned char *)0xE000E406 = configMAX_SYSCALL_INTERRUPT_PRIORITY; 
	*(unsigned char *)0xE000E407 = configMAX_SYSCALL_INTERRUPT_PRIORITY; 

	/*
	 * enable irq6, irq7
	 */
	*(unsigned int *)0xE000E100 = (0x1 << 7) | (0x1 << 6); 

	/*
	 * interrupt enable for user key (pb0, pb1)
	 */
	GPIOB->CRL = (GPIOB->CRL & ~ (0xFF << 0)) | (0x44 << 0);
	AFIO->EXTICR[0] = (AFIO->EXTICR[0]  & ~ (0xFF << 0)) | (0x11 << 0);
	EXTI->FTSR = EXTI->FTSR | (0x3 << 0);
	EXTI->IMR = EXTI->IMR | (0x3 << 0);
}

