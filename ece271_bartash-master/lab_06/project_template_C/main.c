#include "stm32l476xx.h"

void Clock_Init(void);
void GPIO_Init(void);
void SysTick_Initialize(uint32_t ticks); 
void SysTick_Handler(void);
void Delay(uint32_t nTime);

volatile int32_t TimeDelay = 0; 
int ticks = 8000;

int main(void){
	
	int i = 0;
	
	Clock_Init();
	GPIO_Init();
	SysTick_Initialize(ticks); 
	
  // Dead loop & program hangs here 
	/*
	// code to toggle the red LED every second
	while(1) {
	
		Delay(1000); // delay for 1 second
		GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		
	}
	
*/	
/*	
	// Morse code "SOS"
	while(1) {
		for(i = 0; i < 6; i++) {
			Delay(250); // delay for 1/4 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
	
		for(i = 0; i < 6; i++) {
			Delay(500); // delay for 1/4 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
	
		for(i = 0; i < 6; i++) {
			Delay(250); // delay for 1/4 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
	}

*/
	// Morse code "HI KENT"
	while(1) {
		
		for(i = 0; i < 8; i++) { // spells out "H" ....
		Delay(250); // delay for 1/4 second
		GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
		
		Delay(250); // delay for 1/4 second between letters
			
		for(i = 0; i < 4; i++) { // spells out "I" ..
			Delay(250); // delay for 1/4 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
		
		Delay(500); // delay for 1/4 second between words
		
			
		// spells out "K" -.-
		for(i = 0; i < 2; i++) {
			Delay(500); // delay for 1 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
		
		Delay(250); // delay for 1/4 second between letters
		
		for(i = 0; i < 2; i++) {
			Delay(250); // delay for 1 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
		
		Delay(250); // delay for 1/4 second between letters
		
		for(i = 0; i < 2; i++) {
			Delay(500); // delay for 1 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
		
		Delay(250); // delay for 1/4 second between letters
		
		// spells out "E" .
		for(i = 0; i < 2; i++) {
			Delay(250); // delay for 1 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
			
		Delay(250); // delay for 1/4 second between letters

		// spells out "N" -.
		for(i = 0; i < 2; i++) {
			Delay(500); // delay for 1 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
		
		Delay(250); // delay for 1/4 second between letters
		
		for(i = 0; i < 2; i++) {
			Delay(250); // delay for 1 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}
			
		Delay(250); // delay for 1/4 second between letters
			
		// spells out "T" -
		for(i = 0; i < 2; i++) {
			Delay(500); // delay for 1 second
			GPIOB->ODR ^= GPIO_ODR_ODR_2 ; // Toggle red LED
		}	
		
		Delay(500); // delay for 1/2 second between words
		
	}
		
}

	
void Clock_Init(void) {
	
	// Select MSI (Multi Speed Internal) clock range
	RCC->CR &= ~(RCC_CFGR_SW); // Clear
	RCC->CR |= (RCC_CFGR_SW_MSI); // Set
	
  RCC->CR &= ~(RCC_CR_MSIRANGE); // Clear 
  RCC->CR |= RCC_CR_MSIRANGE_7; // Set 8MHz clock
	
	RCC->CR |= RCC_CR_MSIRGSEL; // Sets MSI range
		
	// Enable MSI Clock
  RCC->CR |= ((uint32_t)RCC_CR_MSION);
		
	// wait until MSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_MSIRDY) == 0 ) {;}
}

void GPIO_Init(void) {
	
  // Enable the clock to GPIO Ports A and B	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;  
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;

	GPIOB->MODER &= ~(GPIO_MODER_MODER2) ;   // Clear PB2
  GPIOB->MODER |= (GPIO_MODER_MODER2_0);	// Set bit PB2 as output
	GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_2) ; // PB2 output as Push-Pull
	GPIOB->PUPDR &= ~(GPIO_MODER_MODER2) ; // PB2 output as NO PUPD	

	// MODE: 00: Input mode,              01: General purpose output mode
  //       10: Alternate function mode, 11: Analog mode (reset state)
		
	GPIOA->MODER &= ~(0xCFF) ; // Configure Joy Stick as input
	GPIOA->PUPDR &= ~(0xCFF) ; // Reset Joy Stick as Pull-down
	GPIOA->PUPDR |= (0x8AA) ; // Set Joy Stick as Pull-down

}

// Input: ticks = number of ticks between two interrupts
void SysTick_Initialize(uint32_t ticks) {
	
	SysTick->CTRL = 0; // Disable SysTick IRQ and SysTick counter
	
	SysTick->LOAD = ticks - 1; // Set reload register
	
	// Set interrupt priority of SysTick to least urgency (i.e., largest priority value)
	NVIC_SetPriority (SysTick_IRQn, (1 <<__NVIC_PRIO_BITS) - 1);
	
	SysTick->VAL = 0;		// Reset the SysTick counter value
	
	// Select processor clock: 1 =  processor clock; 0 = external clock
	SysTick->CTRL |= (0x1 << 2);

	// Enables SysTick interrupt, 1 = Enable, 0 = Disable
	SysTick->CTRL |= (0x1 << 1);
	
	// Enable SysTick
	SysTick->CTRL |= 0x1;
	
}

void SysTick_Handler (void) {
	if (TimeDelay > 0)
		TimeDelay--;
}

void Delay (uint32_t nTime) {
	// nTime: specifies the delay time length
	TimeDelay = nTime; // TimeDelay must be declared as volatile
	while(TimeDelay != 0); // Busy wait 
}
