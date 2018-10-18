#include <stdint.h>
#include "stm32l476xx.h"
#include "LCD.h"

void Clock_Init(void);
void Input_Capture_Init(void);
void TIM4_IRQHandler(void);
void PWM_Init(void);
void Delay (uint32_t nTime);
void coolThing(void);

int current_value = 0;
int time_interval = 0;
int old_value = 0;
int overflow = 0;
int distance = 0;

int time_span = 0;

int main(void){
	
	Clock_Init();
	Input_Capture_Init();
	PWM_Init();
	LCD_Initialization();
	LCD_Clear();
		
  // Dead loop & program hangs here
	while(1) {
		
		coolThing(); // code to write value to LCD
		
	}
}

void Clock_Init() {
	
		// Enable High Speed Internal Clock (HSI = 16 MHz)
  RCC->CR |= ((uint32_t)RCC_CR_HSION);
	
  // wait until HSI is ready
  while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
	
  // Select HSI as system clock source 
  RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
  RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;     							// 01: HSI16 oscillator used as system clock

  // Wait till HSI is used as system clock source 
  while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;} 
		
}

void Input_Capture_Init() {
	 // Enable the clock to GPIO Port B, E, A
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; 
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	GPIOB->MODER &= ~(0x03<<12);    					// Clear bit 13 and bit 12
  GPIOB->MODER |= (0x2<<12);								// Set to Alternate Function Mode 
	
	// Clear Pin 6, set Pin 6 to Alternate Function Mode 2
	GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL6;
	GPIOB->AFR[0] |= (0x2<<24);	  
	
	// Configure Port B as No Pull Up No Pull Down
	GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;
	
	/*
	// Configure GPIO port B pin 6 as AF function 
	GPIOB->MODER &= ~(0x3000);
	GPIOB->MODER |= 0x2000;
	*/
	
	// Enable the clock of timer 4
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	
	// Set up an appropriate prescaler to slow down the clock of timer counter
	TIM4->PSC = 15;
	
	// Set the direction as input and select the active input
	TIM4->CCMR1 &= ~TIM_CCMR1_CC1S; // _0
	TIM4->CCMR1 |= 0x1; //
	
	// Program the input filter duration, dispose digital filtering by clearing IC1F[3:0] bits because we want to capture every event
	TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;
	
	// Select the edge of the active transition
	TIM4->CCER |= (1<<1 | 1<<3); // Both rising and falling edge // clear for 1 Hz? 
	// TIM4->CCER |= TIM_CCER_CC1P;
	// TIM4->CCER |= TIM_CCER_CC1NP;
	
	// Program the input prescaler to capture each valid transition, set the input prescaler to zero; IC1PSC[1:0] bits (input capture 1 prescaler)
	TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
	
	// Enable capture of the counter
	// CC1E: Capture/compare interrupt enable for channel 1; 0 = capture disabled, 1 = capture enabled
	TIM4->CCER |= TIM_CCER_CC1E;
	
	// Enable related interrupts
	// CC1IE: Capture/compare interrupt enable for channel 1
	TIM4->DIER |= TIM_DIER_CC1IE;
	
	// CC1DE: Capture/compare DMA request enable for channel 1
	TIM4->DIER |= TIM_DIER_CC1DE;
	
	// TIM4->EGR |= TIM_EGR_UG;
	
	TIM4->DIER |= TIM_DIER_UIE;
	
	// Enable the counter
	TIM4->CR1 |= TIM_CR1_CEN;
	
	// Set priority to 1
	NVIC_SetPriority(TIM4_IRQn, 1);
	
	// Enable TIM4 interupt in NVIC
	NVIC_EnableIRQ(TIM4_IRQn);
}

void TIM4_IRQHandler(void) {
	
	uint32_t current_value;
	
	if(TIM4->SR & TIM_SR_UIF) {
		overflow++;
		TIM4->SR &= ~(TIM_SR_UIF);
	}
	
	if((TIM4->SR & TIM_SR_CC1IF) != 0) { // If update flag is set
		current_value = TIM4->CCR1; // Reading CCR1 clears CC1IF interrupt flag
		time_interval = current_value - old_value + overflow*65535; // if counting up
		overflow = 0;
		old_value = current_value;
	}
}

void PWM_Init() {
	// Enable the clock to GPIO Port E	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	GPIOE->MODER &= ~(0x03<<22);    					// Clear bit 13 and bit 12
  GPIOE->MODER |= (0x2<<22);								// Set to Alternate Function Mode 
	
	// Clear Pin 6, set Pin 6 to Alternate Function Mode 2
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFRH3;
	GPIOE->AFR[1] |= (0x1<<12);	  
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Enable timer clock
	TIM1->PSC = 15; // Prescaler = 15
	TIM1->ARR = 0xFFFF; // Upcounting
	
	// OC1M = 110 for PWM Mode 1 on channel 1
	TIM1->CCMR1 &= ~(TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	TIM1->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	
	TIM1->CCMR1 |= TIM_CCMR1_OC2PE; // Output 1 preload enable
	TIM1->CR1 	|= TIM_CR1_ARPE;	// Auto-reload preload enable
	TIM1->CCER 	|= TIM_CCER_CC2E; // Enable output to channel 1 
	// TIM1->EGR 	|= TIM_EGR_UG; // Force update
	// TIM1->SR 		&= ~TIM_SR_UIF; // Clear the update flag
	TIM1->DIER 	|= TIM_DIER_UIE; // Enable interrupt on update
	TIM1->BDTR 	|= (TIM_BDTR_MOE | TIM_BDTR_OSSR); // Set MOE bit
	TIM1->CR1 	|= TIM_CR1_CEN; // Enable counter
	
	TIM1->CCR2 = 10; // CCR = 10
	
	
	
}

void coolThing(void) {		// cool thing will write to LCD
	
	unsigned char value[6];							//Array to display 
	int pulse, i; 
	int j = 0;	
	
	/*
	pulse = time_interval; 
	for(i=5; i >= 0; i--){
			value[i] = (pulse%10) + 0x30; //0x30 sets screen such that it's all 0's. Pulse%10 converts output to numbers
			pulse/= 10; //display seperate values 
	}
	*/

	distance = time_interval / 58; 
	for(i=5; i >= 0; i--){
			value[i] = (distance%10) + 0x30; //0x30 sets screen such that it's all 0's. Pulse%10 converts output to numbers
			distance /= 10; //display seperate values 
	}
	
	LCD_DisplayString(value);
	for(j=0; j < 1600000; j++) {;} // a short delay
	
}
