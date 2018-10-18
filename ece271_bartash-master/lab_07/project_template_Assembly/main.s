
	INCLUDE core_cm4_constants.s		; Load Cortex-M4 Definitions
	INCLUDE stm32l476xx_constants.s     ; Load STM32L4 Definitions 

	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	IMPORT brightness
	ENTRY			
				
__main	PROC
	
    ; Enable the clock to GPIO Port E	
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR r1, r1, #RCC_AHB2ENR_GPIOEEN
	STR r1, [r0, #RCC_AHB2ENR]
	
	; Configure green LED  as Alternate Function mode
	
	; GPIOE->MODER &= ~(GPIO_MODER_MODER8) ;   // Clear PE8
	; GPIOE->MODER |= (GPIO_MODER_MODER8_1);	// Set bit PE8 as output
	
	LDR r0, =GPIOE_BASE
	LDR r1, [r0, #GPIO_MODER]
	BIC r1, r1, #(GPIO_MODER_MODER8) ; Clear PE8
	ORR r1, r1, #(GPIO_MODER_MODER8_1) ; Set bit PE8 as output
	STR r1, [r0, #GPIO_MODER]
	
	; Configure and select the Alternative Function for PE8
	LDR r0, =GPIOE_BASE
	LDR r1, [r0, #GPIO_AFR1]
	BIC r1, r1, #GPIO_AFRH_AFRH0
	ORR r1, r1, #(0x00000001)
	STR r1, [r0, #GPIO_AFR1]
	
	; GPIOE->PUPDR &= ~(GPIO_MODER_MODER8) ; // PE8 output as NO PUPD
	
	LDR r0, =GPIOE_BASE
	LDR r1, [r0, #GPIO_PUPDR]
	BIC r1, r1, #(GPIO_PUPDR_PUPDR8) ; PE8 output as NO PUPD
	STR r1, [r0, #GPIO_PUPDR]
	
	; Enable the Timer 1 clock
	LDR r7, =RCC_BASE
	LDR r0, [r7, #RCC_APB2ENR]
	ORR r0, r0, #RCC_APB2ENR_TIM1EN
	STR r0, [r7, #RCC_APB2ENR]
	
	LDR r7, =TIM1_BASE
	
	; Set prescaler
	MOV r0, #63
	STR r0, [r7, #TIM_PSC]
	
	; Set auto-reload value
	LDR r0, [r7, #TIM_ARR]
	MOV r1, #TIM_ARR_ARR
	BIC r0, r0, r1
	ORR r0, r0, #199 ; Sets the distance between signals or Duty Cycle of wave
	STR r0, [r7, #TIM_ARR] ; Counts from 0 to 199 (200 steps)
	
	; Set PWM mode on channel 1
	LDR r0, [r7, #TIM_CCMR1]
	LDR r1, =TIM_CCMR1_OC1M
	BIC r0, r0, r1
	ORR r0, r0, #TIM_CCMR1_OC1M_2
	ORR r0, r0, #TIM_CCMR1_OC1M_1
	
	; Enable output preload on channel 1
	ORR r0, r0, #TIM_CCMR1_OC1PE
	STR r0, [r7, #TIM_CCMR1]
	
	; Enable auto-reload preload on channel 1
	LDR r0, [r7, #TIM_CR1]
	BIC r0, r0, #TIM_CR1_ARPE
	ORR r0, r0, #TIM_CR1_ARPE
	STR r0, [r7, #TIM_CR1]
	
	; Enable output on channel 1
	LDR r0, [r7, #TIM_CCER]
	ORR r0, r0, #TIM_CCER_CC1NE
	STR r0, [r7, #TIM_CCER]
	
	; Set MOE bit to 1
	LDR r0, [r7, #TIM_BDTR]
	ORR r0, r0, #TIM_BDTR_MOE
	STR r0, [r7, #TIM_BDTR]
	
	; Set the initial CCR value for channel 1
	LDR r0, [r7, #TIM_CCR1]
	LDR r1, =TIM_CCR1_CCR1
	BIC r0, r0, r1
	ORR r0, r0, #0x0
	STR r0, [r7, #TIM_CCR1]
	
	; Enable the counter on channel 1
	LDR r0, [r7, #TIM_CR1]
	ORR r0, r0, #TIM_CR1_CEN
	STR r0, [r7, #TIM_CR1]

	; MODE: 00: Input mode,              01: General purpose output mode
    ;       10: Alternate function mode, 11: Analog mode (reset state)
	; LDR r0, =GPIOB_BASE
	; LDR r1, [r0, #GPIO_MODER]
	; EOR r1, r1, #(0x03<<(2*2))
	; ORR r1, r1, #(1<<4)
	; STR r1, [r0, #GPIO_MODER]

	; LDR r1, [r0, #GPIO_ODR]
	; ORR r1, r1, #(1<<2)
	; STR r1, [r0, #GPIO_ODR]
	
	BL brightness
  
stop 	B 		stop     		; dead loop & program hangs here

	ENDP
					
	ALIGN			

	AREA    myData, DATA, READWRITE
	ALIGN
array	DCD   1, 2, 3, 4
	END
