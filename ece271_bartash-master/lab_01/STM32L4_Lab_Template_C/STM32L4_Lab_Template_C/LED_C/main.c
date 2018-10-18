#include "stm32l476xx.h"

int main(void){
	
	// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;  //01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
  
  // Enable the clock to GPIO Port B, Port A, and Port E	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	// MODE: 00: Input mode, 01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
  
	GPIOB->MODER &= ~(GPIO_MODER_MODER2) ;   // Clear PB2
  GPIOB->MODER |= (GPIO_MODER_MODER2_0);	// Set bit PB2 as output
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_2) ; // PB2 output as Push-Pull
	GPIOB->PUPDR &= ~(GPIO_MODER_MODER2) ; // PB2 output as NO PUPD
		
	GPIOE->MODER &= ~(GPIO_MODER_MODER8) ;   // Clear PE8
  GPIOE->MODER |= (GPIO_MODER_MODER8_0);	// Set bit PE8 as output
	GPIOE->OTYPER &= ~(GPIO_OTYPER_OT_8) ; // PE8 output as Push-Pull
	GPIOE->PUPDR &= ~(GPIO_MODER_MODER8) ; // PE8 output as NO PUPD
		
	GPIOA->MODER &= ~(0xCFF) ; // Configure Joy Stick as input
	GPIOA->PUPDR &= ~(0xCFF) ; // Reset Joy Stick as Pull-down
	GPIOA->PUPDR |= (0x8AA) ; // Set Joy Stick as Pull-down
		
	GPIOB->ODR |= GPIO_ODR_ODR_2;
  // Dead loop & program hangs here
	while(1) {
		if(GPIOA->IDR & GPIO_IDR_IDR_0) { // if the center is pressed
			GPIOE->ODR ^= GPIO_ODR_ODR_8 ;
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ;
			while(GPIOA->IDR & GPIO_IDR_IDR_0) ;
			}
		// new code
		if(GPIOA->IDR & GPIO_IDR_IDR_1) { // if the left side is pressed
			GPIOE->ODR |= GPIO_ODR_ODR_8 ; // Turn on
			while(GPIOA->IDR & GPIO_IDR_IDR_1) ;
			}
		if(GPIOA->IDR & GPIO_IDR_IDR_2) { // if the right side is pressed
			GPIOB->ODR |= GPIO_ODR_ODR_2 ; // Turn on
			while(GPIOA->IDR & GPIO_IDR_IDR_2) ;
			}
		if(GPIOA->IDR & GPIO_IDR_IDR_3) { // if the up is pressed
			GPIOE->ODR &= ~(GPIO_ODR_ODR_8) ; // Turn off
			while(GPIOA->IDR & GPIO_IDR_IDR_1) ;
			}
		if(GPIOA->IDR & GPIO_IDR_IDR_5) { // if the down is pressed
			GPIOB->ODR &= ~(GPIO_ODR_ODR_2) ; // Turn off
			while(GPIOA->IDR & GPIO_IDR_IDR_2) ;
			}
		}
}
