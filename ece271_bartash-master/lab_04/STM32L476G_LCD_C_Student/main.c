#include "stm32l476xx.h"
#include "lcd.h"

void System_Clock_Init(void);

int i = 0;
uint8_t c = '0';
int p = 0;

int main(void){
	
	System_Clock_Init(); // Enables the clock
	LCD_Initialization(); // Function that calls several other functions: LCD_PIN_Init(), LCD_Clock_Init(), LCD_Configure(), LCD_Clear()
	LCD_Clear();
	
	// Enable the clock to GPIO Ports A, B, and E	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	// Configure Port E: Pin 10, 11, 12, and 13 as Digital Output
	GPIOE->MODER &= ~(0x0FF00000); // Clear
	GPIOE->MODER |= (0x05500000); // Set
	
	// Configure Port A: Pin 1, 2, and 3 as Digital Input
	GPIOA->MODER &= ~(0xFC); // Clear
	GPIOA->MODER |= (0x0); // Set
	
	while(1) {
		start:
		GPIOE->ODR &= ~(0x3C00); // Set row outputs to zero
		
		for(i = 0; i < 10000; i++); // Short delay for software debouncing
		
		// Check Column 1
		if((GPIOA->IDR & 0x02) == 0) {
			while(1) {
				GPIOE->ODR &= ~(0x3C00);	// Check row 1
				GPIOE->ODR |= 0x3800; // Set row output to 0b1110
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x02) == 0) {
					c = '1';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
				
				GPIOE->ODR &= ~(0x3C00);	// Check row 2
				GPIOE->ODR |= 0x3400; // Set row output to 0b1101
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x02) == 0) {
					c = '4';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
				
				GPIOE->ODR &= ~(0x3C00);	// Check row 3
				GPIOE->ODR |= 0x2C00; // Set row output to 0b1011
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x02) == 0) {
					c = '7';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
					
				GPIOE->ODR &= ~(0x3C00);	// Check row 4
				GPIOE->ODR |= 0x1C00; // Set row output to 0b1110
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x02) == 0) {
					c = '*';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
			}
		}
		
		// Check Column 2
		if((GPIOA->IDR & 0x04) == 0) {
			while(1) {
				GPIOE->ODR &= ~(0x3C00);	// Check row 1
				GPIOE->ODR |= 0x3800; // Set row output to 0b1110
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x04) == 0) {
					c = '2';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
				
				GPIOE->ODR &= ~(0x3C00);	// Check row 2
				GPIOE->ODR |= 0x3400; // Set row output to 0b1101
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x04) == 0) {
					c = '5';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
				
				GPIOE->ODR &= ~(0x3C00);	// Check row 3
				GPIOE->ODR |= 0x2C00; // Set row output to 0b1011
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x04) == 0) {
					c = '8';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
					
				GPIOE->ODR &= ~(0x3C00);	// Check row 4
				GPIOE->ODR |= 0x1C00; // Set row output to 0b1110
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x04) == 0) {
					c = '0';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
			}
		}
		
		// Check Column 3
		if((GPIOA->IDR & 0x08) == 0) {
			while(1) {
				GPIOE->ODR &= ~(0x3C00);	// Check row 1
				GPIOE->ODR |= 0x3800; // Set row output to 0b1110
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x08) == 0) {
					c = '3';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
				
				GPIOE->ODR &= ~(0x3C00);	// Check row 2
				GPIOE->ODR |= 0x3400; // Set row output to 0b1101
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x08) == 0) {
					c = '6';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
				
				GPIOE->ODR &= ~(0x3C00);	// Check row 3
				GPIOE->ODR |= 0x2C00; // Set row output to 0b1011
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x08) == 0) {
					c = '9';
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
					
				GPIOE->ODR &= ~(0x3C00);	// Check row 4
				GPIOE->ODR |= 0x1C00; // Set row output to 0b1110
				
				for(i = 0; i < 10000; i++); // Short delay for software debouncing
				
				if((GPIOA->IDR & 0x08) == 0) {
					LCD_WriteChar(&c, 0, 0, p++ %6);
					for(i = 0; i < 1000000; i++); // Longer delay for software debouncing
					
					goto start;
				}
			}
		}
	} 
}

void System_Clock_Init(void){
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 );
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 );
		
}



// Function definitions here
/*
signed char getkey() { // Function to identify the column and row of the pressed key
	int i, j;
	signed char out = -1;
	
	GPIOE->ODR &= ~(0x3C00); // Clear Pins 10, 11, 12, 13
	// GPIOE->ODR |= 0x01 << i; 
	
	for(i = 0; i < 10000; i++) {;} // Short delay for software debouncing
	
	for (i = 0; i < 4; i++) { // Scan columns
		
		GPIOE->ODR |= 0x3C00; // Clear Pins 10, 11, 12, 13
	  GPIOE->ODR &= ~(0x400 << i); 
		
		if(GPIOA->IDR != 1) {
			for (j = 0; j < 3; j++) { // Scan rows
			if(GPIOA->IDR & (0x02 << j)) {
				out = 3 * i + j;
				}
			}
		return out;
		}
	}
}

signed char mapkey(signed char key) { // Function to determine the key of row and column
	char KEY[12] = {1, 2, 3, 4, 5, 6, 7, 8, 9, '*', 0, '#'};
	if(key > -1 && key < 12) {
		return KEY[key];
	}
	else  {
		return -1;
	}
}

signed int getnum(void) {
	int result = 0, temp = 0;
	while (temp != '#') {
		while (temp != -1) {
			temp = mapkey(getkey());
		}
		
		temp = mapkey(getkey());
		
		if (temp >= 0 && temp <= 9) {
			if (result < 0) {
				result *= -1;
				result *= 10;
				result += temp;
				result *= -1;
			}
			else {
				result *= 10;
				result += temp;
			}
		}
		else if (temp == 10) {
			result *= -1;
		}
		else if (temp == '*') {
			result /= 10;
		}
	}
	return result;
}


char getpw(char size, char buff[]) {
	signed char temp = 0, slot = 0;
	static int test = 0;
	temp = mapkey(getkey());
	while (temp != '#') {
		while ((temp = mapkey(getkey())) == -1); // while not pressed, keep capturing
		while (mapkey(getkey()) != -1); // wait for release
		if (temp == '#') {
			return slot;
		}
		if (temp >= 0 && temp <= 13 && slot <= size - 1) {
			buff[slot] = temp;
			slot++;
			printf(" \n \n \n \n \n");
			for(int i = 0; i < slot; i++) {
				printf("*");
			}
		}
		else if (temp == '*' && slot != 0) {
			slot--;
			printf(" \n \n \n \n \n");
			for(int i = 0; i < slot; i++) {
				printf("*");
			}
		}
	}
} 

void mydelayms(unsigned int ms) {
	int i, j;
	for (i = 0; i < ms; i++) {
		for (j = 0; j < 70; j++) {
			
		}
	}
*/