#include "stm32f10x.h"
#include "key.h"

uint8_t key_is_pressed(int n)
{
	uint8_t pressed = 0;	

	if (n == KEY_LEFT)
	{
		pressed = (GPIOA->IDR & (0x1 << 3)) ? 0:1;
	}
	else if (n == KEY_CENTER)
	{
		pressed = (GPIOA->IDR & (0x1 << 2)) ? 0:1;
	}
	else if (n == KEY_RIGHT)
	{
		pressed = (GPIOA->IDR & (0x1 << 4)) ? 0:1;
	}	

	return pressed;
}

void key_init()
{
	/*
	 * enable clock for port-b, port-a, afio ip
	 */
	RCC->APB2ENR = RCC->APB2ENR | (0x1 << 2) | (0x1 << 0);
	
	/*
	 * input enable for user key (pa2, pa3, pa4)
	 */
	GPIOA->CRL = (GPIOA->CRL & ~ (0xFFF << 8)) | (0x444 << 8);
}

