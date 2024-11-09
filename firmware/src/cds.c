#include "stm32f10x.h"
#include "cds.h"


void cds_init()
{
	/*
	 * enable clock for adc-1, and port-A
	 */
	RCC->APB2ENR = RCC->APB2ENR | (0x1 << 9) | (0x1 << 2);
	
	/*
	 * analog input enable for pa1
	 */
	GPIOA->CRL = GPIOA->CRL & ~ (0xF << 4);

	/*
	 * 1st conversion in regular sequence
	 */
	ADC1->SQR3 = 0x1;
	
	/*
	 * sw trigger event, continuous conversion, adc on
	 */
	ADC1->CR2 = ADC1->CR2 | (0x7 << 17) | (0x1 << 1) | (0x1 << 0);
	
	/*
	 * start conversion, trigger conversion
	 */
	ADC1->CR2 = ADC1->CR2 | (0x1 << 22) | (0x1 << 20);
}

uint16_t cds_get_value()
{
	return ADC1->DR & 0x0FFFF;
}
