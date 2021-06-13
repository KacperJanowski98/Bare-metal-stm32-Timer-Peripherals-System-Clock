/*
 * peripherals.h
 *
 *  Created on: Jun 13, 2021
 *      Author: Kacper Janowski
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include "main.h"

void stop_timer(TIM_TypeDef *TIMx);
void start_timer(TIM_TypeDef *TIMx, uint16_t ms);

#endif /* PERIPHERALS_H_ */
