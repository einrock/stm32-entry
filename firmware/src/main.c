#include <stdio.h>
#include "stm32f10x.h"
#include "uart.h"
#include "led.h"
#include "key.h"
#include "fnd.h"
#include "cds.h"
#include "exti.h"

static unsigned int gTickCount;

/*
 * interrupt service handler for exti-0 (pb0), up key
 */
void EXTI0_IRQHandler(void)
{
	EXTI->PR = (0x1 << 0);	
	printf("%s \r\n", __func__);
}

/*
 * interrupt service handler for exti-1 (pb1), down key
 */
void EXTI1_IRQHandler(void)
{
	EXTI->PR = (0x1 << 1);
	printf("%s \r\n", __func__);
}

/*
 * system timer interrupt handler
 */
void SysTick_Handler(void)
{
	gTickCount = gTickCount + 1;
}

/*
 * 
 */
void delay(uint32_t msec)
{
	uint32_t next_tick = gTickCount + msec;
	while (gTickCount < next_tick)
	{
	}
}

/*
 * systick initialization (enable interrupt every 1msec) 
 */
void systick_init()
{
	*(unsigned int *)0xE000E010 = 0x7;
	*(unsigned int *)0xE000E014 = 72000 - 1;
}

/*
 * 
 */
int main()
{
	systick_init();
	uart_init();
	led_init();
	key_init();
	fnd_init();
	cds_init();
	exti_init();

	led_off_all();	

	uint32_t k = 0;
	while (1)
	{
		/*
		 * check if one of LEFT, CENTER, RIGHT keys is pressed or not
		 */
		if (key_is_pressed(KEY_LEFT))
		{
			printf("LEFT KEY PESSED \r\n");
		}
		else if (key_is_pressed(KEY_CENTER))
		{
			printf("CENTER KEY PESSED \r\n");
		}
		else if (key_is_pressed(KEY_RIGHT))
		{
			printf("RIGHT KEY PESSED \r\n");
		}

		/*
		 * turn on the LEDs one by one in order
		 */
		if ((k%5)==0)
		{
			static uint32_t n = 0;
			led_off_all();
			led_on(LED_0 + n);
			n = (n + 1) % 8;
		}		
		
		/*
		 * perform stop watch using FND module
		 */
		uint32_t tick;
		uint32_t a0, a1, a2, a3;
		
		tick = gTickCount;
		a3 = (tick / 10) % 10;
		a2 = (tick / 100) % 10;
		a1 = (tick / 1000) % 10;
		a0 = (tick / 10000) % 10;
		
		fnd_display_number(0, a0);
		delay(5);
		
		fnd_display_number(1, a1);
		delay(5);
		
		fnd_display_number(2, a2);
		delay(5);

		fnd_display_number(3, a3);
		delay(5);
		
		/*
		 * read cds sensing value every 200msec 
		 */
		if ((k%10) == 0)
		{
			printf("CDS Value : %d \r\n", cds_get_value());	
		}
		
		k = k + 1;		
	}
	
	return 0;
}
