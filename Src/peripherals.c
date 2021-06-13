/*
 * peripherals.c
 *
 *  Created on: Jun 13, 2021
 *      Author: Kacper Janowski
 */

#include "peripherals.h"

/**
 * Start basic timer
 */
void start_timer(TIM_TypeDef *TIMx, uint16_t ms) {
	// Start by making sure the timer's counter is off
	TIMx->CR1 &= ~(TIM_CR1_CEN);
	// Reset the peripheral
	if (TIMx == TIM2) {
		RCC->APB1RSTR |= (RCC_APB1RSTR_TIM2RST);
		RCC->APB1RSTR &= ~(RCC_APB1RSTR_TIM2RST);
	}
	// Set the timer prescaler/autoreload timing registers
	TIMx->PSC = core_clock_hz / 1000;
	TIMx->ARR = ms;
	// Send an update event to reset the timer and apply settings
	TIMx->EGR |= TIM_EGR_UG;
	// Enable the hardware interrupt
	TIMx->DIER |= TIM_DIER_UIE;
	// Enable the timer
	TIMx->CR1 |= TIM_CR1_CEN;
}

/**
 * Stop a running timer on a given Timer peripheral
 */
void stop_timer(TIM_TypeDef *TIMx) {
	// Turn off the timer's counter
	TIMx->CR1 &= ~(TIM_CR1_CEN);
	// Clear the pending update interrupt flag
	TIMx->SR &= ~(TIM_SR_UIF);
}








