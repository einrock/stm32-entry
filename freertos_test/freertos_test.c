#include "stdio.h"
#include "stm32f10x.h"
#include "uart.h"
#include "led.h"
#include "key.h"
#include "fnd.h"
#include "cds.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
#include "semphr.h"

QueueHandle_t xQueue;
SemaphoreHandle_t xSemaphore;

TaskHandle_t hTaskA;
TaskHandle_t hTaskB;
TaskHandle_t hTaskC;
TaskHandle_t hTaskD;
TaskHandle_t hTaskE;

/*
 *
 */
void vApplicationIdleHook()
{
	__nop();
}

/*
 *
 */
void Task_A(void * param)
{		
	for( ;; )
	{	
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
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
		xSemaphoreGive(xSemaphore);
		
		vTaskDelay(100);			
	}
}

/*
 *
 */
void Task_B(void * param)
{		
	unsigned int n = 0;
	for( ;; )
	{	
		led_off_all();
		led_on(LED_0 + n);
		n = (n + 1) % 8;

		vTaskDelay(100);			
	}
}

/*
 *
 */
void Task_C(void * param)
{
	unsigned int tick = 0;

	while (1)
	{
		unsigned int a0, a1, a2, a3;

		xQueueReceive(xQueue, &tick, 0);

		a3 = (tick / 1) % 10;
		a2 = (tick / 10) % 10;
		a1 = (tick / 100) % 10;
		a0 = (tick / 1000) % 10;

		fnd_display_number(0, a0);
		vTaskDelay(5);

		fnd_display_number(1, a1);
		vTaskDelay(5);

		fnd_display_number(2, a2);
		vTaskDelay(5);

		fnd_display_number(3, a3);
		vTaskDelay(5);		
	}
}

/*
 *
 */
void Task_D(void * param)
{		
	for( ;; )
	{	
		xSemaphoreTake(xSemaphore, portMAX_DELAY);
		printf("CDS Value : %d \r\n", cds_get_value());
		xSemaphoreGive(xSemaphore);
		
		vTaskDelay(100);			
	}
}

/*
 *
 */
void Task_E(void * param)
{
	unsigned int fnd_tick = 0;
	unsigned int start = 1;
	unsigned int last_tick = xTaskGetTickCount();	

	while (1)
	{		
		int value = ulTaskNotifyTake(pdTRUE, 0);
		if (value == 1)
		{
			start = start ^ 1;
		}
		else if (value == 2)
		{
			fnd_tick = 0;
		}

		if (start)
		{
			fnd_tick = fnd_tick + 1;
		}

		xQueueSend(xQueue, &fnd_tick, portMAX_DELAY);
		vTaskDelayUntil(&last_tick, 100);		
	}
}

/*
 *
 */
void freertos_testing()
{
	xTaskCreate(Task_A,
			"task a", 
			configMINIMAL_STACK_SIZE,     
			NULL,    
			tskIDLE_PRIORITY,
			&hTaskA );     

	xTaskCreate(Task_B,
			"task b", 
			configMINIMAL_STACK_SIZE,     
			NULL,    
			tskIDLE_PRIORITY,
			&hTaskB );     

	xTaskCreate(Task_C,
			"task c", 
			configMINIMAL_STACK_SIZE,     
			NULL,    
			tskIDLE_PRIORITY + 1,
			&hTaskC );     

	xTaskCreate(Task_D,
			"task c", 
			configMINIMAL_STACK_SIZE,     
			NULL,    
			tskIDLE_PRIORITY,
			&hTaskD );     

	xTaskCreate(Task_E,
			"task c", 
			configMINIMAL_STACK_SIZE,     
			NULL,    
			tskIDLE_PRIORITY,
			&hTaskE );     

	xQueue = xQueueCreate(8, sizeof(int));
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphore);
	
	vTaskStartScheduler();

	// never get here.
}


