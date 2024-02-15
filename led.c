#include "stm32f10x.h"
#include "led.h"

void led_on(int n)
{
	if (n == LED_0)
	{
		GPIOA->ODR = GPIOA->ODR & ~ (0x1 << 5);
	}
	else if (n == LED_1)
	{
		GPIOA->ODR = GPIOA->ODR & ~ (0x1 << 6);
	}
	else if (n == LED_2)
	{
		GPIOA->ODR = GPIOA->ODR & ~ (0x1 << 7);
	}
	else if (n == LED_3)
	{
		GPIOA->ODR = GPIOA->ODR & ~ (0x1 << 8);
	}
	else if (n == LED_4)
	{
		GPIOC->ODR = GPIOC->ODR & ~ (0x1 << 8);
	}
	else if (n == LED_5)
	{
		GPIOC->ODR = GPIOC->ODR & ~ (0x1 << 9);
	}
	else if (n == LED_6)
	{
		GPIOC->ODR = GPIOC->ODR & ~ (0x1 << 10);
	}
	else if (n == LED_7)
	{
		GPIOC->ODR = GPIOC->ODR & ~ (0x1 << 11);
	}
}

void led_off(int n)
{
	if (n == LED_0)
	{
		GPIOA->ODR = GPIOA->ODR | (0x1 << 5);
	}
	else if (n == LED_1)
	{
		GPIOA->ODR = GPIOA->ODR | (0x1 << 6);
	}
	else if (n == LED_2)
	{
		GPIOA->ODR = GPIOA->ODR | (0x1 << 7);
	}
	else if (n == LED_3)
	{
		GPIOA->ODR = GPIOA->ODR | (0x1 << 8);
	}
	else if (n == LED_4)
	{
		GPIOC->ODR = GPIOC->ODR | (0x1 << 8);
	}
	else if (n == LED_5)
	{
		GPIOC->ODR = GPIOC->ODR | (0x1 << 9);
	}
	else if (n == LED_6)
	{
		GPIOC->ODR = GPIOC->ODR | (0x1 << 10);
	}
	else if (n == LED_7)
	{
		GPIOC->ODR = GPIOC->ODR | (0x1 << 11);
	}
}

void led_toggle(int n)
{
	if (n == LED_0)
	{
		GPIOA->ODR = GPIOA->ODR ^ (0x1 << 5);
	}
	else if (n == LED_1)
	{
		GPIOA->ODR = GPIOA->ODR ^ (0x1 << 6);
	}
	else if (n == LED_2)
	{
		GPIOA->ODR = GPIOA->ODR ^ (0x1 << 7);
	}
	else if (n == LED_3)
	{
		GPIOA->ODR = GPIOA->ODR ^ (0x1 << 8);
	}
	else if (n == LED_4)
	{
		GPIOC->ODR = GPIOC->ODR ^ (0x1 << 8);
	}
	else if (n == LED_5)
	{
		GPIOC->ODR = GPIOC->ODR ^ (0x1 << 9);
	}
	else if (n == LED_6)
	{
		GPIOC->ODR = GPIOC->ODR ^ (0x1 << 10);
	}
	else if (n == LED_7)
	{
		GPIOC->ODR = GPIOC->ODR ^ (0x1 << 11);
	}
}

void led_off_all()
{
	GPIOA->ODR = GPIOA->ODR | (0xF << 5);
	GPIOC->ODR = GPIOC->ODR | (0xF << 8);
}

void led_on_all()
{
	GPIOA->ODR = GPIOA->ODR & ~ (0xF << 5);
	GPIOC->ODR = GPIOC->ODR & ~ (0xF << 8);
}

void led_init()
{
	/*
	 * enable clock for port-c, port-a
	 */
	RCC->APB2ENR = RCC->APB2ENR | (0x1 << 4) | (0x1 << 2);
	
	/*
	 * output enable for leds (pa5 ~ pa7)
	 */
	GPIOA->CRL = (GPIOA->CRL & ~ (0xFFFU << 20)) | (0x333 << 20);

	/*
	 * output enable for leds (pa8)
	 */
	GPIOA->CRH = (GPIOA->CRH & ~ (0xF << 0)) | (0x3 << 0);

	/*
	 * output enable for leds (pc8 ~ pc11)
	 */
	GPIOC->CRH = (GPIOC->CRH & ~ (0xFFFF << 0)) | (0x3333 << 0);
}

