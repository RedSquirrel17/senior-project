#include <stdint.h>
#include "stm32l476xx.h"
#include "LCD.h"

// int time_interval = 0;
extern int distance;

void coolThing(void) {		// cool thing will write to LCD
	
	unsigned char value[6];							//Array to display 
	int pulse, i; 
	int j = 0;	
	
	/*//
	pulse = time_interval; 
	for(i=5; i >= 0; i--){
			value[i] = (pulse%10) + 0x30; //0x30 sets screen such that it's all 0's. Pulse%10 converts output to numbers
			pulse/= 10; //display seperate values 
	}
	//*/

	// distance = time_interval / 58; 
	for(i=5; i >= 0; i--){
			value[i] = (distance%10) + 0x30; //0x30 sets screen such that it's all 0's. Pulse%10 converts output to numbers
			distance /= 10; //display seperate values 
	}
	
	LCD_DisplayString(value);
	for(j=0; j < 1600000; j++) {;} // a short delay
	
}
