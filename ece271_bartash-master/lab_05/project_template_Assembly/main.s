
	INCLUDE core_cm4_constants.s		; Load Cortex-M4 Definitions
	INCLUDE stm32l476xx_constants.s     ; Load STM32L4 Definitions 

	AREA    main, CODE, READONLY
	EXPORT	__main				; make __main visible to linker
	ENTRY			
				
__main	PROC
	
    ; Enable the clock to GPIO Port B	
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR r1, r1, #RCC_AHB2ENR_GPIOBEN
	STR r1, [r0, #RCC_AHB2ENR]
	
	; Enable the clock to GPIO Port A
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR r1, r1, #RCC_AHB2ENR_GPIOAEN
	STR r1, [r0, #RCC_AHB2ENR]
	
	; Enable the clock to GPIO Port E
	LDR r0, =RCC_BASE
	LDR r1, [r0, #RCC_AHB2ENR]
	ORR r1, r1, #RCC_AHB2ENR_GPIOEEN
	STR r1, [r0, #RCC_AHB2ENR]
	
	; MODE: 00: Input mode,              01: General purpose output mode
    ;       10: Alternate function mode, 11: Analog mode (reset state)
	
	; GPIOB->MODER &= ~(GPIO_MODER_MODER2) ;   // Clear PB2
	; GPIOB->MODER |= (GPIO_MODER_MODER2_0);	// Set bit PB2 as output
	; GPIOB->OTYPER &= ~(GPIO_OTYPER_OT_2) ; // PB2 output as Push-Pull
	; GPIOB->PUPDR &= ~(GPIO_MODER_MODER2) ; // PB2 output as NO PUPD
	
	LDR r0, =GPIOB_BASE
	LDR r1, [r0, #GPIO_MODER]
	BIC r1, r1, #(GPIO_MODER_MODER2) ; Clear PB2
	ORR r1, r1, #(GPIO_MODER_MODER2_0) ; Set bit PB2 as output
	STR r1, [r0, #GPIO_MODER]
	LDR r1, [r0, #GPIO_OTYPER] ; PB2 output as Push-Pull
	BIC r1, r1, #(GPIO_OTYPER_OT_2)
	STR r1, [r0, #GPIO_OTYPER]
	LDR r1, [r0, #GPIO_PUPDR] ; PB2 output as NO PUPD
	BIC r1, r1, #(GPIO_MODER_MODER2)
	STR r1, [r0, #GPIO_PUPDR]
	
	; GPIOE->MODER &= ~(GPIO_MODER_MODER8) ;   // Clear PE8
	; GPIOE->MODER |= (GPIO_MODER_MODER8_0);	// Set bit PE8 as output
	; GPIOE->OTYPER &= ~(GPIO_OTYPER_OT_8) ; // PE8 output as Push-Pull
	; GPIOE->PUPDR &= ~(GPIO_MODER_MODER8) ; // PE8 output as NO PUPD
	
	LDR r0, =GPIOE_BASE
	LDR r1, [r0, #GPIO_MODER]
	BIC r1, r1, #(GPIO_MODER_MODER8) ; Clear PE8
	ORR r1, r1, #(GPIO_MODER_MODER8_0) ; Set bit PE8 as output
	STR r1, [r0, #GPIO_MODER]
	LDR r1, [r0, #GPIO_OTYPER]
	BIC r1, r1, #(GPIO_OTYPER_OT_8) ; PE8 output as Push-Pull
	STR r1, [r0, #GPIO_OTYPER]
	LDR r1, [r0, #GPIO_PUPDR]
	BIC r1, r1, #(GPIO_MODER_MODER8) ; PE8 output as NO PUPD
	STR r1, [r0, #GPIO_PUPDR]
	
	; GPIOA->MODER &= ~(0xCFF) ; // Configure Joy Stick as input
	; GPIOA->PUPDR &= ~(0xCFF) ; // Reset Joy Stick as Pull-down
	; GPIOA->PUPDR |= (0x8AA) ; // Set Joy Stick as Pull-down
	
	LDR r0, =GPIOA_BASE
	LDR r1, [r0, #GPIO_MODER] ; Configure Joy Stick as input
	MOV r2, #0xCFF
	BIC r1, r1, r2
	STR r1, [r0, #GPIO_MODER]
	LDR r1, [r0, #GPIO_PUPDR]
	BIC r1, r1, r2 ; Reset Joy Stick as Pull-down
	MOV r2, #0x8AA
	ORR r1, r1, r2 ; Set Joy Stick as Pull-down
	STR r1, [r0, #GPIO_PUPDR]
	
;stop 	B 		stop     		; dead loop & program hangs here

	; while(1) {
		; if(GPIOA->IDR & GPIO_IDR_IDR_0) { // if the center is pressed
			; GPIOE->ODR ^= GPIO_ODR_ODR_8 ;
			; GPIOB->ODR ^= GPIO_ODR_ODR_2 ;
			; while(GPIOA->IDR & GPIO_IDR_IDR_0) ;
			; }
			
loop	
		LDR r0, =GPIOA_BASE
		LDR r1, [r0, #GPIO_IDR] ; if the center is pressed
		AND r2, r1, #GPIO_IDR_IDR_0 ; &
		CMP r2, #0
		BNE debounce ; continue at "debounce"
		
		AND r2, r1, #GPIO_IDR_IDR_1 ; if the left is pressed
		CMP r2, #0
		BNE left ; continue at "left"
		
		AND r2, r1, #GPIO_IDR_IDR_2 ; if the right is pressed
		CMP r2, #0
		BNE right ; continue at "right"
		
		AND r2, r1, #GPIO_IDR_IDR_3 ; if the down arrow is pressed
		CMP r2, #0
		BNE down ; continue at "down"
		
		AND r2, r1, #GPIO_IDR_IDR_5 ; if the up arrow is pressed
		CMP r2, #0
		BNE up ; continue at "up"
		
		BEQ loop ; go back to the start of the loop
		
		
debounce 
		LDR r1, [r0, #GPIO_IDR] ; toggle the red and green LEDs
		AND r2, r1, #GPIO_IDR_IDR_0 ; &
		CMP r2, #0
		BNE debounce
		
		LDR r0, =GPIOE_BASE
		LDR r1, [r0, #GPIO_ODR]
		EOR r1, r1, #GPIO_ODR_ODR_8 ; ^=
		STR r1, [r0, #GPIO_ODR]
		LDR r0, =GPIOB_BASE
		LDR r1, [r0, #GPIO_ODR]
		EOR r1, r1, #GPIO_ODR_ODR_2 ; ^=
		STR r1, [r0, #GPIO_ODR]
		B loop
		
		; if(GPIOA->IDR & GPIO_IDR_IDR_1) { // if the left side is pressed
			; GPIOE->ODR |= GPIO_ODR_ODR_8 ; // Turn on
			; while(GPIOA->IDR & GPIO_IDR_IDR_1) ;
			; }
			
	
left		
		LDR r0, =GPIOE_BASE ; Turn on the green LED
		LDR r1, [r0, #GPIO_ODR]
		ORR r1, r1, #GPIO_ODR_ODR_8 ; |=
		STR r1, [r0, #GPIO_ODR]
		B loop
		
		; if(GPIOA->IDR & GPIO_IDR_IDR_2) { // if the right side is pressed
			; GPIOB->ODR |= GPIO_ODR_ODR_2 ; // Turn on
			; while(GPIOA->IDR & GPIO_IDR_IDR_2) ;
			; }

right
		LDR r0, =GPIOB_BASE ; Turn on the red LED
		LDR r1, [r0, #GPIO_ODR]
		ORR r1, r1, #GPIO_ODR_ODR_2 ; |=
		STR r1, [r0, #GPIO_ODR]
		B loop
		
		; if(GPIOA->IDR & GPIO_IDR_IDR_3) { // if the up is pressed
			; GPIOE->ODR &= ~(GPIO_ODR_ODR_8) ; // Turn off
			; while(GPIOA->IDR & GPIO_IDR_IDR_1) ;
			; }

up
		LDR r0, =GPIOE_BASE ; Turn off the red LED
		LDR r1, [r0, #GPIO_ODR]
		BIC r1, r1, #GPIO_ODR_ODR_8 ; &= ~
		STR r1, [r0, #GPIO_ODR]
		B loop
			
		; if(GPIOA->IDR & GPIO_IDR_IDR_5) { // if the down is pressed
			; GPIOB->ODR &= ~(GPIO_ODR_ODR_2) ; // Turn off
			; while(GPIOA->IDR & GPIO_IDR_IDR_2) ;
			; }
			
down
		LDR r0, =GPIOB_BASE ; Turn off the green LED
		LDR r1, [r0, #GPIO_ODR]
		BIC r1, r1, #GPIO_ODR_ODR_2 ; &= ~
		STR r1, [r0, #GPIO_ODR]
		B loop
		
		B loop	
endloop
			
		; }

	ENDP
					
	ALIGN			

	AREA    myData, DATA, READWRITE
	ALIGN
array	DCD   1, 2, 3, 4
	END
