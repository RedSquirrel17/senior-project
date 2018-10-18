#include "stm32l476xx.h"

// RGB LED bonus lab

void Clock_Init(void);
void GPIO_Init(void);

void DMA_init(void);
void Timer_Init(void);

int SRC_Buffer[48];


int current_value = 0;
int time_interval = 0;
int old_value = 0;
int overflow = 0;
int distance = 0;

int time_span = 0;

int main(void){
	
//	// red
//	if(i > 8 && i < 16) {
//			SRC_Buffer[i] = 8;
//		}
//		else {
//			SRC_Buffer[i] = 2;
//		}
		
//	// orange
//	if(i > 4 && i < 16) {
//			SRC_Buffer[i] = 8;
//		}
//		else {
//			SRC_Buffer[i] = 2;
//		}
	
//	// yellow
//	if(i > 16) {
//			SRC_Buffer[i] = 2;
//		}
//		else {
//			SRC_Buffer[i] = 8;
//		}
	
//	// green 
//		if(i > 8) {
//			SRC_Buffer[i] = 2;
//		}
//		else {
//			SRC_Buffer[i] = 8;
//		}
	
//	// blue
//	if(i < 16) {
//			SRC_Buffer[i] = 2;
//		}
//		else {
//			SRC_Buffer[i] = 8;
//		}
		
//	// purple
//	if(i < 8) {
//			SRC_Buffer[i] = 2;
//		}
//		else {
//			SRC_Buffer[i] = 8;
//		}

//	// pink
//	if(i > 4 && i < 16) { 
//			SRC_Buffer[i] = 8;
//		}
//		else {
//			SRC_Buffer[i] = 2;
//		}
	
	int i = 0;
	
	Clock_Init();
	GPIO_Init(); 
	
	for(i = 0; i < 24; i++) {
		
		// SRC_Buffer[i] = 8;
		
	if(i > 8 && i < 16) {
			SRC_Buffer[i] = 8;
		}
		else {
			SRC_Buffer[i] = 2;
		}
	}
	
	for(i = 24; i < 48; i++) {
		
			SRC_Buffer[i] = 8; // white LED
				
//		if(i > 32) {
//			SRC_Buffer[i] = 2;
//		}
//		else {
//			SRC_Buffer[i] = 8;
//		}
		
	}
	
	DMA_init();
	Timer_Init();
	
  // Dead loop & program hangs here 
	while(1);

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
	
  // Enable the clock to GPIO Ports A, B, and E	
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;  
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;

	GPIOE->MODER &= ~(GPIO_MODER_MODER8) ;   // Clear PE8
  GPIOE->MODER |= (GPIO_MODER_MODER8_1);	// Set bit PE8 as output
	GPIOE->OTYPER &= ~(GPIO_OTYPER_OT_8) ; // PE8 output as Push-Pull
	GPIOE->PUPDR &= ~GPIO_PUPDR_PUPDR8;		// PE8 output as NO PUPD				 
	
	// Clear, set PE8 to Alternate Function Mode 1
	GPIOE->AFR[1] &= ~GPIO_AFRH_AFRH0;
	GPIOE->AFR[1] |= (0x1);	  

}

void DMA_init(void) {
	
	// DMA1 clock enable
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA1EN;
	
	// Enable memory to memory code
	DMA1_Channel2->CCR &= ~DMA_CCR_MEM2MEM;
	
	// Peripheral transfer size (PSIZE)
	DMA1_Channel2->CCR &= ~(0x3 << 8); // 00: 8-bits, 01: 16-bits, 10: 32-bits
	DMA1_Channel2->CCR |= (0x2 << 8);
	
	// Memory transfer size
	DMA1_Channel2->CCR &= ~(0x3 << 10); // 00: 8-bits, 01: 16-bits, 10: 32-bits
	DMA1_Channel2->CCR |= (0x2 << 10);
	
	// Enable memory increment mode
	DMA1_Channel2->CCR |= (0x1 << 7);
	
	// Disable peripheral increment mode
	DMA1_Channel2->CCR &= ~(0x1 << 6);
	
	// Disable circular mode
	DMA1_Channel2->CCR &= ~(0x1 << 5);
	
	// Set the transfer direction, memory to peripherial
	DMA1_Channel2->CCR |= (0x1 << 4);
	
	// DMA channel x number of data register (DMA_CNDTRx)
	DMA1_Channel2->CNDTR = 48; // 24;
	
	// DMA channel x peripheral address register (DMA_CPARx)
	DMA1_Channel2->CPAR = (unsigned int) &TIM1->CCR1;
	
	// DMA channel x memory address register (DMA_CMARx)
	DMA1_Channel2->CMAR = (unsigned int) SRC_Buffer;
	
	// NVIC_SetPriority(DMA1_Channel2_IRQn, 1); // Set priority to 1
	// NVIC_EnableIRQ(DMA1_Channel2_IRQn); // Enable DMA interrupt
	
	DMA1_CSELR->CSELR &= ~(DMA_CSELR_C2S); // Clear the channel selection register
	DMA1_CSELR->CSELR |= (0x7 << 4); // Channel 2 mapped on TIM1_CH1
	
	// Enable channel 2
	DMA1_Channel2->CCR |= 0x1;
	
}

void Timer_Init() {
	
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN; // Enable timer clock
	TIM1->PSC = 0; // Prescaler = 1
	TIM1->ARR = 9; // ARR = 10
	
	// OC1M = 110 for PWM Mode 1 on channel 1
	TIM1->CCMR1 &= ~(TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	TIM1->CCMR1 |= (TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	
	TIM1->CCMR1 |= TIM_CCMR1_OC1PE; // Output 1 preload enable
	TIM1->CR1 	|= TIM_CR1_ARPE;	// Auto-reload preload enable
	TIM1->CCER 	|= TIM_CCER_CC1NE; // Enable output to channel 1 
	TIM1->BDTR 	|= TIM_BDTR_MOE; // Set MOE bit
	
	TIM1->CR1 |= TIM_CR1_URS; // Update request source overflow
	TIM1->DIER |= TIM_DIER_CC1DE; 
	
	TIM1->CR1 	|= TIM_CR1_CEN; // Enable counter
	
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
