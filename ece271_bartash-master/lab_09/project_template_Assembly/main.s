
	INCLUDE core_cm4_constants.s		; Load Cortex-M4 Definitions
	INCLUDE stm32l476xx_constants.s     ; Load STM32L4 Definitions 

	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	
	IMPORT coolThing
	IMPORT LCD_Initialization
	IMPORT LCD_Clear
	ENTRY			
				
__main	PROC
	
	BL HSI_init
	
    ; Enable the clock to GPIO Port B
	;RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN; 
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR r1, r1, #RCC_AHB2ENR_GPIOBEN
	STR r1, [r0, #RCC_AHB2ENR]
	
	;// Enable the clock to GPIO Port E 
	;RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR r1, r1, #RCC_AHB2ENR_GPIOEEN
	STR r1, [r0, #RCC_AHB2ENR]
	
	;GPIOB->MODER &= ~(0x03<<12);
	;GPIOB->MODER |= (0x2<<12);
	LDR r0, =GPIOB_BASE
	LDR r1, [r0, #GPIO_MODER]
	BIC r1, r1, #(0x03<<12) ; // Clear bit 13 and bit 12
	ORR r1, r1, #(0x2<<12) ; // Set to Alternate Function Mode 
	STR r1, [r0, #GPIO_MODER]
	
	;// Clear Pin 6, set Pin 6 to Alternate Function Mode 2
	;GPIOB->AFR[0] &= ~GPIO_AFRL_AFRL6;
	;GPIOB->AFR[0] |= (0x2<<24);	
	LDR r1, [r0, #GPIO_AFR0]
	BIC r1, r1, #(GPIO_AFRL_AFRL6) 
	ORR r1, r1, #(0x2<<24) 
	STR r1, [r0, #GPIO_AFR0]
	
	;set GPIOE pin 11 to alternate function
	LDR  r7, =GPIOE_BASE
	LDR  r2, [r7, #GPIO_MODER]
	BIC  r2, r2, #(0x03<<(2*11))
	ORR  r2, r2, #(0x2<<(2*11))
	STR  r2, [R7, #GPIO_MODER]
		
	;PE11 alt func 1
	LDR  r2, [r7, #GPIO_AFR1]
	BIC  r2, r2, #(0xF<<(12))
	ORR  r2, r2, #(0x1<<(12))
	STR  r2, [R7, #GPIO_AFR1]
	
	;// Enable the clock of timers 4 and 1
	;RCC->APB1ENR1 |= RCC_APB1ENR1_TIM4EN;
	LDR r7, =RCC_BASE
	LDR r0, [r7, #RCC_APB1ENR1]
	BIC r0, r0, #RCC_APB1ENR1_TIM4EN
	ORR r0, r0, #RCC_APB1ENR1_TIM4EN
	STR r0, [r7, #RCC_APB1ENR1]
	
	LDR r0, =RCC_BASE
	LDR  r0, [r7, #RCC_APB2ENR]
	BIC  r0, r0, #RCC_APB2ENR_TIM1EN
	ORR  r0, r0, #RCC_APB2ENR_TIM1EN
	STR  r0, [r7, #RCC_APB2ENR]
	
	;Set up PB6 for input capture
	
	LDR r7, =TIM4_BASE
	
	;// Set up an appropriate prescaler to slow down the clock of timer counter
	;TIM4->PSC = 15;
	LDR r0, [r7, #TIM_PSC]
	MOV r0, #15
	STR r0, [r7, #TIM_PSC]
	
	;// Set the direction as input and select the active input
	;TIM4->CCMR1 &= ~TIM_CCMR1_CC1S;
	;TIM4->CCMR1 |= 0x1; 
	LDR r0, [r7, #TIM_CCMR1]
	BIC r0, r0, #(TIM_CCMR1_CC1S)
	ORR r1, r1, #0x1
	
	;// Program the input filter duration, dispose digital filtering by clearing IC1F[3:0] bits because we want to capture every event
	;TIM4->CCMR1 &= ~TIM_CCMR1_IC1F;
	BIC r0, r0, #(TIM_CCMR1_IC1F)
	STR r1, [r0, #TIM_CCMR1]
	
	;;// Select the edge of the active transition
	;;TIM4->CCER |= (1<<1 | 1<<3); // Both rising and falling edge // clear for 1 Hz? 
	;LDR r0, [r1, #TIM_CCER]
	;ORR r1, r1, #(1<<1)
	;ORR r1, r1, #(1<<3)
	;STR r1, [r0, #TIM_CCER]
	
	LDR  r0, [r7, #TIM_CCER]
	ORR  r0, r0, #0x000A ;rising and falling edge capture
	STR  r0, [r7, #TIM_CCER]
	
	;// Program the input prescaler to capture each valid transition, set the input prescaler to zero; IC1PSC[1:0] bits (input capture 1 prescaler)
	;TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
	LDR r0, [r7, #TIM_CCMR1]
	BIC r0, r0, #TIM_CCMR1_IC1PSC
	STR r0, [r7, #TIM_CCMR1]
	
	;// Enable capture of the counter
	;// CC1E: Capture/compare interrupt enable for channel 1; 0 = capture disabled, 1 = capture enabled
	;TIM4->CCER |= TIM_CCER_CC1E;
	LDR r0, [r7, #TIM_CCER]
	ORR r0, r0, #TIM_CCER_CC1E
	STR r0, [r7, #TIM_CCER]
	
	;// Enable related interrupts
	;// CC1IE: Capture/compare interrupt enable for channel 1
	;TIM4->DIER |= TIM_DIER_CC1IE;
	
	;// CC1DE: Capture/compare DMA request enable for channel 1
	;TIM4->DIER |= TIM_DIER_CC1DE;
	;TIM4->DIER |= TIM_DIER_UIE;
	LDR  r0, [r7, #TIM_DIER]
	ORR  r0, r0, #TIM_DIER_CC1IE
	ORR  r0, r0, #TIM_DIER_CC1DE
	ORR  r0, r0, #TIM_DIER_UIE
	STR  r0, [r7, #TIM_DIER]
	
	;// Enable the counter
	;TIM4->CR1 |= TIM_CR1_CEN;
	LDR r0, [r7, #TIM_CR1]
	ORR r0, r0, #TIM_CR1_CEN
	STR r0, [r7, #TIM_CR1]
	
	;// Set priority to 1
	;NVIC_SetPriority(TIM4_IRQn, 1);
	;// Enable TIM4 interupt in NVIC
	;NVIC_EnableIRQ(TIM4_IRQn);
	MOV r0, #TIM4_IRQn
	MOV r1, #1
	BL NVIC_SetPriority
	MOV r0, #TIM4_IRQn
	MOV r1, #1
	BL Enable
	
	; Initialization of PWM output (PWM_Init() function from Lab 8)
	
	LDR r7, =TIM1_BASE
	
	; Set prescaler
	LDR  r0, [r7, #TIM_PSC]
	MOV r0, #15
	STR r0, [r7, #TIM_PSC]
	
	; TIM1->ARR = 0xFFFF; // Upcounting
	LDR  r0, [r7, #TIM_ARR]
	MOV r0, #65499
	STR r0, [r7, #TIM_ARR]
	
	;; Set auto-reload value
	;LDR r0, [r7, #TIM_ARR]
	;MOV r1, #TIM_ARR_ARR
	;BIC r0, r0, r1
	;ORR r0, r0, #199 ; Sets the distance between signals or Duty Cycle of wave
	;STR r0, [r7, #TIM_ARR] ; Counts from 0 to 199 (200 steps)
	
	;// OC1M = 110 for PWM Mode 1 on channel 1
	;TIM1->CCMR1 &= ~(TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	;TIM1->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	; Set PWM mode on channel 1
	LDR r0, [r7, #TIM_CCMR1]
	LDR r1, =TIM_CCMR1_OC2M ; =0x01007000
	BIC r0, r0, r1
	ORR r0, r0, #TIM_CCMR1_OC2M_2
	ORR r0, r0, #TIM_CCMR1_OC2M_1
	STR r0, [r7, #TIM_CCR1]
	
	; TIM1->CCMR1 |= TIM_CCMR1_OC2PE; // Output 1 preload enable
	; Enable output preload on channel 1
	ORR r0, r0, #TIM_CCMR1_OC2PE
	STR r0, [r7, #TIM_CCMR1]
	
	; TIM1->CR1 	|= TIM_CR1_ARPE;	// Auto-reload preload enable
	; Enable auto-reload preload on channel 1
	LDR r0, [r7, #TIM_CR1]
	ORR r0, r0, #TIM_CR1_ARPE
	STR r0, [r7, #TIM_CR1]
	
	; TIM1->CCER 	|= TIM_CCER_CC2E; // Enable output to channel 1 
	; Enable output on channel 1
	LDR r0, [r7, #TIM_CCER]
	ORR r0, r0, #TIM_CCER_CC2E ; #0x00000050
	STR r0, [r7, #TIM_CCER]
	
	;; TIM1->DIER 	|= TIM_DIER_UIE; // Enable interrupt on update
	;LDR r0, [r7, #TIM_DIER]
	;ORR r0, r0, #TIM_DIER_UIE
	;STR r0, [r7, #TIM_DIER] 
	
	; TIM1->BDTR 	|= (TIM_BDTR_MOE | TIM_BDTR_OSSR); // Set MOE bit
	; Set MOE bit to 1
	LDR r0, [r7, #TIM_BDTR]
	ORR r0, r0, #TIM_BDTR_MOE ; 0x8C00
	ORR r0, r0, #TIM_BDTR_OSSR ; 0x8C00
	STR r0, [r7, #TIM_BDTR]
	
	;; Set the initial CCR value for channel 1
	;LDR r0, [r7, #TIM_CCR1]
	;LDR r1, =TIM_CCR1_CCR1
	;BIC r0, r0, r1
	;ORR r0, r0, #0x0
	;STR r0, [r7, #TIM_CCR1]
	
	; TIM1->CCR2 = 10; // CCR = 10
	LDR r0, [r7, #TIM_CCR2]
	MOV r0, #10
	STR r0, [r7, #TIM_CCR2]
	
	; TIM1->CR1 	|= TIM_CR1_CEN; // Enable counter
	; Enable the counter on channel 1
	LDR r0, [r7, #TIM_CR1]
	ORR r0, r0, #TIM_CR1_CEN
	STR r0, [r7, #TIM_CR1]
	
	BL LCD_Initialization ;Initialize the LCD
	BL LCD_Clear ;Clear the LCD
		
	;set output duty cycle for PE11
	LDR r7, =TIM1_BASE
	LDR  r0, [r7, #TIM_CCR2]
	MOV  r0, #10
	STR  r0, [r7, #TIM_CCR2]
	
  
stop 	BL coolThing

		B 		stop     		; dead loop & program hangs here

		ENDP
		ALIGN

; Select HSI (high-speed internal, 16 MHz, 1% accuracy) as the system clock.
HSI_init PROC
		 ; EXPORT HSI_init
		 LDR r0, =RCC_BASE
		 
		 ; Turn on HSI oscillator
		 LDR r1, [r0, #RCC_CR]
		 ORR r1, r1, #RCC_CR_HSION
		 STR r1, [r0, #RCC_CR]
		 
		 ; Select HSI as system clock
		 LDR r1, [r0, #RCC_CFGR]
		 BIC r1, r1, #RCC_CFGR_SW
		 ORR r1, r1, #RCC_CFGR_SW_HSI
		 STR r1, [r0, #RCC_CFGR]
		 
		 ; Wait for HSI stable
WaitHSI  LDR r1, [r0, #RCC_CR]
		 AND r1, r1, #RCC_CR_HSIRDY
		 CMP r1, #0
		 BEQ WaitHSI
		 
		 BX LR
		 ENDP
			 
TIM4_IRQHandler PROC
			EXPORT TIM4_IRQHandler
			PUSH {r4, r6, r10, lr}
			
			LDR r0, =TIM4_BASE
			LDR r2, [r0, #TIM_SR]
			AND r3, r2, #TIM_SR_UIF ; Check update event flag
			CBZ r3, check_CC
			
			LDR r3, =overflow 
			LDR r1, [r3]
			ADD r1, r1, #1 ; Increment overflow counter
			STR r1, [r3]
			
			BIC r2, r2, #TIM_SR_UIF ; Clear update event flag
			STR r2, [r0, #TIM_SR]
			
check_CC	ADD r2, r2, #TIM_SR_CC1IF
			CBZ r2, exit
			
			; Fetch the current CCR value
			LDR r0, =TIM4_BASE
			LDR r1, [r0, #TIM_CCR1] ; Read the capture value
			
			LDR r2, =lastCounter
			LDR r0, [r2] ; load the last counter value
			STR r1, [r2] ; save the new counter value
			CBZ r0, clearOverflow
			
			LDR r3, =overflow
			LDR r4, [r3] ; load the overflow value
			LSL r4, r4, #16 ; X 65536
			ADD r6, r1, r4
			SUB r10, r6, r0 ; r10 = timer counter difference
			LDR r2, =timespan
			STR r10, [r2]
			
clearOverflow
			MOV r0, #0
			LDR r3, =overflow
			STR r0, [r3] ; clear overflow counter
			
exit		POP {r4, r6, r10, pc}
			ENDP
			ALIGN	


Enable PROC
	   PUSH {r0-r4, lr}
	   AND r2, r0, #0x1F
  	   MOV r3, #1
	   LSL r3,r3,r2
	   LDR r4, =NVIC_BASE
	   CMP r1, #0
       LDRNE r1, =NVIC_ISER0
	   LDREQ r1, =NVIC_ICER0
	   ADD r1, r4, r1
	   LSR r2, r0, #5
	   LSL r2, r2, #2
	   STR r3, [r1, r2]
	   POP {r0-r4, pc}
	   ENDP
	
NVIC_SetPriority PROC
	PUSH {r0-r4, lr}
	LSLS r2, r1, #4
	LDR r3, =NVIC_BASE
	LDR r4, =NVIC_IP0
	ADD r3, r3, r4
	STRB r2, [r3,r0]
	POP {r0-r4, pc}
	ENDP

	AREA    myData, DATA, READWRITE
	ALIGN
	EXPORT distance
		
array	DCD   1, 2, 3, 4
	
timespan 	DCD 0 ; the pulse width
lastCounter DCD 0 ; the timer counter value of last capture event
overflow 	DCD 0 ; counter the number of overflows
distance    DCD 0 ; distance in cm
	
	END
		