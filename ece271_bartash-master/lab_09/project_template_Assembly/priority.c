#include <stdint.h>
#include "stm32l476xx.h"

int priority(void) {

	// Set priority to 1
	NVIC_SetPriority(TIM4_IRQn, 1);
	
	// Enable TIM4 interupt in NVIC
	NVIC_EnableIRQ(TIM4_IRQn);
	
}