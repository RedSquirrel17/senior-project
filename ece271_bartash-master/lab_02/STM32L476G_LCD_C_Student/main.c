#include "stm32l476xx.h"
#include "lcd.h"

void System_Clock_Init(void);

int main(void){
	LCD_Initialization(); // function that calls several other functions: LCD_PIN_Init(), LCD_Clock_Init(), LCD_Configure(), LCD_Clear();
	
	// Enable the clock to GPIO Port A	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	GPIOA->MODER &= ~(0xCFF) ; // Configure Joy Stick as input
	GPIOA->MODER |= (0) ; // Set Joy Stick 
	GPIOA->PUPDR &= ~(0xCFF) ; // Reset Joy Stick as Pull-down
	GPIOA->PUPDR |= (0x8AA) ; // Set Joy Stick as Pull-down
	
	while(1){
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
