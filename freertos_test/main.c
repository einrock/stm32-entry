#include "stdio.h"
#include "stm32f10x.h"
#include "uart.h"
#include "led.h"
#include "key.h"
#include "fnd.h"
#include "cds.h"

#include "FreeRTOS.h"
#include "semphr.h"

extern SemaphoreHandle_t xSemaphoreUart;
extern QueueHandle_t xQueue;
extern TaskHandle_t hTaskE;

/*
 *
 */
void EXTI0_IRQHandler(void)
{
	EXTI->PR = (0x1 << 0);	
	//printf("%s \r\n", __func__);
#if 1	
	vTaskNotifyGiveFromISR(hTaskE, NULL);
#else	
	xTaskNotifyFromISR(hTaskE, 1, eSetValueWithOverwrite, NULL);
#endif
}

/*
 *
 */
void EXTI1_IRQHandler(void)
{
	EXTI->PR = (0x1 << 1);
	//printf("%s \r\n", __func__);
#if 1	
	vTaskNotifyGiveFromISR(hTaskE, NULL);
	vTaskNotifyGiveFromISR(hTaskE, NULL);
#else	
	xTaskNotifyFromISR(hTaskE, 2, eSetValueWithOverwrite, NULL);
#endif
}	

void main()
{	
	uart_init();
	led_init();
	key_init();
	fnd_init();
	cds_init();

	led_off_all();	
	freertos_testing();
}
