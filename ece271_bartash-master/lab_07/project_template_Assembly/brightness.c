#include "stm32l476xx.h"

void brightness(void) {

int i;
int brightness = 1;
int stepSize = 1;

	while(1) {
		if((brightness >= 200) || (brightness <= 0))
			stepSize = -stepSize; 	// Reverse direction
		brightness += stepSize; 	// Change brightness
		TIM1->CCR1 = brightness; 	// Set brightness for channel 1
		for(i = 0; i < 10000; i++); // Short delay
	}
}
