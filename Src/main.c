/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Kacper Janowski
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#include "main.h"

int main(void)
{
	// Initial clock setup

    FLASH->ACR &= ~(0x00000017);
    FLASH->ACR |=  (FLASH_ACR_LATENCY | FLASH_ACR_PRFTEN);

    RCC->CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_MCO1PRE);
    RCC->CFGR |=  (RCC_CFGR_MCO1PRE_2 | RCC_CFGR_RTCPRE_4);
    // Turn the PLL on and wait for it to be ready.
    RCC->CR |=  (RCC_CR_PLLON);
    while (!(RCC->CR & RCC_CR_PLLRDY)) {};
    // Select the PLL as the system clock source.
    RCC->CFGR &= ~(RCC_CFGR_SW);
    RCC->CFGR |=  (RCC_CFGR_SW_PLL);
    while (!(RCC->CFGR & RCC_CFGR_SWS_PLL)) {};
    // Set the global clock speed variable.
    core_clock_hz = 48000000;

    // Enable the GPIOD clock
    RCC->AHB1ENR |=  RCC_AHB1ENR_GPIODEN;
    // Enable the TIM2 clock
    RCC->APB1ENR |= RCC_APB1ENR_TIM12EN;

    // Setup GPIO pin D12
    GPIOD->MODER &= ~(0x3 << (LED_PIN*2));
    GPIOD->MODER |= (0x1 << (LED_PIN*2));
    GPIOD->OTYPER &= ~(0x1 << LED_PIN);
    GPIOD->PUPDR &= ~(0x3 << (LED_PIN*2));

    // Enable the NVIC interrupt for TIM2.
    // (Timer peripheral initialized and used elsewhere)
    NVIC_SetPriority(TIM2_IRQn, 0x03);
    NVIC_EnableIRQ(TIM2_IRQn);
    // Start the timer.
    start_timer(TIM2, 1000);

	while(1)
	{

	}
}
