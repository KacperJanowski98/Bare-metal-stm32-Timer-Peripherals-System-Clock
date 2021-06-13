/*
 * interrupts.c
 *
 *  Created on: Jun 13, 2021
 *      Author: Kacper Janowski
 */

#include "interrupts.h"

void TIM2_IRQ_handler(void) {
	// Handle a timer 'update' interrupt event
	if(TIM2->SR & TIM_SR_UIF) {
		TIM2->SR &= ~(TIM_SR_UIF);
		GPIOD->ODR ^= (1<<LED_PIN);
	}
}
