#include "stm32l476xx.h"
#include "lcd.h"

void System_Clock_Init(void);

int main(void){
	
	//unsigned char FullStep[4] = {0x9, 0xA, 0x6, 0x5};
	unsigned char HalfStep[8] = {0x9, 0x8, 0xA, 0x2, 0x6, 0x4, 0x5, 0x1};
	
	int A, Ao, B, Bo;
	int i, j, k, l;
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;     // 01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
  
  // Enable the clock to GPIO Port B	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;   

	// MODE: 00: Input mode,              01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
  GPIOB->MODER &= ~(0x03<<(2*2)) ;   // Clear bit 13 and bit 12
  GPIOB->MODER |= (1<<4);
		
	GPIOB->ODR |= GPIO_ODR_ODR_2;
	
	LCD_Initialization(); // function that calls several other functions: LCD_PIN_Init(), LCD_Clock_Init(), LCD_Configure(), LCD_Clear();
	
	// Enable the clock to GPIO Port A	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	GPIOA->MODER &= ~(0xCFF) ; // Configure Joy Stick as input
	GPIOA->MODER |= (0) ; // Set Joy Stick 
	GPIOA->PUPDR &= ~(0xCFF) ; // Reset Joy Stick as Pull-down
	GPIOA->PUPDR |= (0x8AA) ; // Set Joy Stick as Pull-down
	
	while(1){
	GPIOB->MODER &= ~(0xF0F0) ; // Clears Port B
	GPIOB->MODER |= (0x5050) ;
		
	GPIOB->OTYPER &= ~(0xC0C0) ;
	GPIOB->PUPDR &= ~(0xF0F0) ;
	
	// Full step: 0b1001, 0b1010, 0b0110, 0b0101
	// Each four-bit sequence represents the ON/OFF control of A, Ao, B, and Bo
	/*	
		if(GPIOA->IDR & GPIO_IDR_IDR_3) { // if the up arrow is pressed
			LCD_DisplayString((uint8_t*) "CW 360");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			LCD_DisplayString((uint8_t*) "DEGREE");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			for(j = 0; j < 512; j++) { // 48 steps x 7.5 degrees per step = 360 degrees
				for(i = 0; i < 4; i++) { // Motor will turn clockwise
					for(k = 0; k < 10000; k++) {;} // A short delay
					
					A = (FullStep[i] & 0x8) >> 3 ;
					Ao = (FullStep[i] & 0x4) >> 2 ;
					B = (FullStep[i] & 0x2) >> 1 ;
					Bo = FullStep[i] & 0x1 ;
				
					GPIOB->ODR &= ~(0xCC) ; // Set the value of the GPIO Output Data Register
					GPIOB->ODR |= A << 2 ;
					GPIOB->ODR |= Ao << 3 ;
					GPIOB->ODR |= B << 6 ;
					GPIOB->ODR |= Bo << 7 ;
					}
					
				}
			while(GPIOA->IDR & GPIO_IDR_IDR_3); // debouncing to prevent joy stick error
			LCD_Clear();
			}
		
		
		if(GPIOA->IDR & GPIO_IDR_IDR_1) { // if the left arrow is pressed
			LCD_DisplayString((uint8_t*) "CW 180");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			LCD_DisplayString((uint8_t*) "DEGREE");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			for(j = 0; j < 256; j++) { // 48 steps x 7.5 degrees per step = 180 degrees
				for(i = 0; i < 4; i++) { // Motor will turn clockwise
					for(k = 0; k < 10000; k++) {;} // A short delay
					A = (FullStep[i] & 0x8) >> 3 ;
					Ao = (FullStep[i] & 0x4) >> 2 ;
					B = (FullStep[i] & 0x2) >> 1 ;
					Bo = FullStep[i] & 0x1 ;
				
					GPIOB->ODR &= ~(0xCC) ; // Set the value of the GPIO Output Data Register
					GPIOB->ODR |= A << 2 ;
					GPIOB->ODR |= Ao << 3 ;
					GPIOB->ODR |= B << 6 ;
					GPIOB->ODR |= Bo << 7 ;
					}
				}
			while(GPIOA->IDR & GPIO_IDR_IDR_1); // debouncing to prevent joy stick error
			}
		
		if(GPIOA->IDR & GPIO_IDR_IDR_5) { // if the down arrow is pressed
			LCD_DisplayString((uint8_t*) "CCW360");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			LCD_DisplayString((uint8_t*) "DEGREE");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			for(j = 0; j < 512; j++) { // 48 steps x 7.5 degrees per step = 360 degrees
				for(i = 3; i >= 0; i--) { // Motor will turn counterclockwise
					for(k = 0; k < 10000; k++) {;} // A short delay
					A = (FullStep[i] & 0x8) >> 3 ;
					Ao = (FullStep[i] & 0x4) >> 2 ;
					B = (FullStep[i] & 0x2) >> 1 ;
					Bo = FullStep[i] & 0x1 ;
				
					GPIOB->ODR &= ~(0xCC) ; // Set the value of the GPIO Output Data Register
					GPIOB->ODR |= A << 2 ;
					GPIOB->ODR |= Ao << 3 ;
					GPIOB->ODR |= B << 6 ;
					GPIOB->ODR |= Bo << 7 ;
					}
				}
			while(GPIOA->IDR & GPIO_IDR_IDR_5); // debouncing to prevent joy stick error
			}
		
		if(GPIOA->IDR & GPIO_IDR_IDR_2) { // if the down arrow is pressed
			LCD_DisplayString((uint8_t*) "CCW180");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			LCD_DisplayString((uint8_t*) "DEGREE");
			for(l=0; l < 1600000; l++) {;}
			LCD_Clear();
			for(j = 0; j < 256; j++) { // 48 steps x 7.5 degrees per step = 180 degrees
				for(i = 3; i >= 0; i--) { // Motor will turn counterclockwise
					for(k = 0; k < 10000; k++) {;} // A short delay
					A = (FullStep[i] & 0x8) >> 3 ;
					Ao = (FullStep[i] & 0x4) >> 2 ;
					B = (FullStep[i] & 0x2) >> 1 ;
					Bo = FullStep[i] & 0x1 ;
				
					GPIOB->ODR &= ~(0xCC) ; // Set the value of the GPIO Output Data Register
					GPIOB->ODR |= A << 2 ;
					GPIOB->ODR |= Ao << 3 ;
					GPIOB->ODR |= B << 6 ;
					GPIOB->ODR |= Bo << 7 ;
					}
				}
			while(GPIOA->IDR & GPIO_IDR_IDR_2); // debouncing to prevent joy stick error
			}
		*/
		
		// Code for Half-stepping
		// Half step: 0b1001, 0b1000, 0b1010, 0b0010, 0b0110, 0b0100, 0b0101, 0b0001
		// Each four-bit sequence represents the ON/OFF control of A, Ao, B, and Bo
	
		for(j = 0; j < 1184; j++) { // 96 steps x 3.75 degrees per step = 360 degrees
			for(i = 0; i < 8; i++) { // Motor will turn clockwise
				for(k = 0; k < 8000; k++) {;} // A short delay
				A = (HalfStep[i] & 0x8) >> 3 ;
				Ao = (HalfStep[i] & 0x4) >> 2 ;
				B = (HalfStep[i] & 0x2) >> 1 ;
				Bo = HalfStep[i] & 0x1 ;
				
				GPIOB->ODR &= ~(0xCC) ; // Set the value of the GPIO Output Data Register
				GPIOB->ODR |= A << 2 ;
				GPIOB->ODR |= Ao << 3 ;
				GPIOB->ODR |= B << 6 ;
				GPIOB->ODR |= Bo << 7 ;
					
			}
		}
	
	/*	
		if(GPIOA->IDR & GPIO_IDR_IDR_0) { // if the center is pressed
			LCD_Clear();
			LCD_Display_Name();
			// LCD_DisplayString((uint8_t*)"ECE271");
			LCD->FCR &= ~(LCD_FCR_CC) ; // Clears LCD_FCR contrast register
			LCD->FCR |= LCD_FCR_CC_1 ; // Sets contrast to medium value
			}
		if(GPIOA->IDR & GPIO_IDR_IDR_1) { // if the left side is pressed
			LCD->FCR &= ~(LCD_FCR_CC) ; // Clears LCD_FCR contrast register
			LCD->FCR |= LCD_FCR_CC_0 ; // Sets contrast to low value
			}
		if(GPIOA->IDR & GPIO_IDR_IDR_2) { // if the right side is pressed
			LCD->FCR &= ~(LCD_FCR_CC) ; // Clears LCD_FCR contrast register
			LCD->FCR |= LCD_FCR_CC ; // Sets contrast to high value
			}
	*/
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
