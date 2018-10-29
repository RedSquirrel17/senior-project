#include "stm32l476xx.h"
#include "lcd.h"
#define VREF 3

void ADC_Wakeup(void);
void ADC_Config(void);
void LCD_Display_Voltage(uint16_t num);
volatile uint16_t ADC_Result;

int main(void){
    // Enable High Speed Internal Clock (HSI = 16 MHz)
    RCC->CR |= ((uint32_t)RCC_CR_HSION);
    // wait until HSI is ready
    while ( (RCC->CR & (uint32_t) RCC_CR_HSIRDY) == 0 ) {;}
    // Select HSI as system clock source
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= (uint32_t)RCC_CFGR_SW_HSI;
    // 01: HSI16 oscillator used as system clock
    // Wait till HSI is used as system clock source
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) == 0 ) {;}
    // Enable the clock to GPIO Port A
    //RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
    RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
    LCD_Initialization();
    
    // Configure PE8 (green LED) as output
    GPIOE->MODER &= ~(3UL<<16); //clears bits 16 & 17
    GPIOE->MODER |= 1UL<<16; //sets bit 16
    //Configure PE8 output as push pull
    GPIOE->OTYPER &= ~(1UL<<7);
    //Configure PE8 output as no pull up no pull down
    GPIOE->PUPDR &= ~(3UL<<16);
    
    //Connect PA0 to ADC
    GPIOA->ASCR |= GPIO_ASCR_EN_0;
    ADC_Config();
    //PA0 is input channel, it is set to analog by default
    ADC1->CR |= ADC_CR_ADSTART; //begin conversions
    // Dead loop & program hangs here
    while(1);
}

void ADC_Config(void){
    //Enable ADC clock
    RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
    //Turn off ADC Conversion
    ADC1->CR &= ~ADC_CR_ADEN;
    ADC1->CR &= ~ADC_CR_ADSTART;
    ADC1->CR &= ~ADC_CR_JADSTART; //turn off jdstart
    //Enable I/O analog switches voltage booster
    ADC123_COMMON->CCR |= SYSCFG_CFGR1_BOOSTEN;
    //Enable conversion of internal channels
    ADC123_COMMON->CCR |= ADC_CCR_VREFEN;
    //Set prescalar to 0
    ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;
    //Synchronous clock mode HCLK/1
    ADC123_COMMON->CCR &= ~ADC_CCR_CKMODE;
    ADC123_COMMON->CCR |= ADC_CCR_CKMODE_0;
    //Configure all ADCs as independent
    ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;
    //Wake up ADC
    ADC_Wakeup();
    //Set resolution to 12 bit ADC
    ADC1->CFGR &= ~ADC_CFGR_RES;
    //Right Alignment
    ADC1->CFGR &= ~ADC_CFGR_ALIGN;
    //Set length of regular channel sequence to 1
    ADC1->SQR1 &= ~ADC_SQR1_L;
    //Set Channel 5 as first conversion in regular sequence
    ADC1->SQR1 &= ~ADC_SQR1_SQ1;
    ADC1->SQR1 |= (ADC_SQR1_SQ1_0 | ADC_SQR1_SQ1_2);
    //Configure channel 5 as single-ended
    ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_5;
    //Configure sample time register for channel 5
    ADC1->SMPR1 &= ~ADC_SMPR1_SMP5; //every 12.5 clock cycles
    ADC1->SMPR1 |= (ADC_SMPR1_SMP5_1);
    //Enable end of conversion interrupt
    ADC1->IER |= ADC_IER_EOC;
    //Enable continuous conversion mode
    ADC1->CFGR &= ~ADC_CFGR_DISCEN;
    ADC1->CFGR |= ADC_CFGR_CONT;
    //Configure delay section as delayed until converted data is read
    //ADC123_COMMON->CCR |= ADC_CCR_DELAY_3; //arbitrary?
    ADC1->CFGR |= ADC_CFGR_AUTDLY;
    //Enable interrupt of ADC1_IRQn
    NVIC_EnableIRQ(ADC1_2_IRQn);
    //Set priority number low, gives high priority
    NVIC_SetPriority(ADC1_2_IRQn, 1);
    //Enable ADC1
    ADC1->CR |= ADC_CR_ADEN;
    //wait until ADC1 is ready
    while(ADC1->ISR & ADC_ISR_ADRDY);
}

void ADC_Wakeup(void){
    int wait;
    
    //if in deep power down mode, exit deep power down mode
    if ((ADC1->CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD){
        ADC1->CR &= ~ADC_CR_DEEPPWD;
    }
    //enable ADC internal voltage regulator
    ADC1->CR |= ADC_CR_ADVREGEN;
    //wait for ADC voltage regulator start-up time
    wait = 20 * (80000000 / 1000000);
    while(wait){
        wait--;
    }
}

void ADC1_2_IRQHandler(void){
    if(ADC1->ISR & ADC_ISR_EOC){
        ADC_Result = ADC1->DR;
        ADC_Result = ADC_Result * 1000 * VREF/ 4096; //converts to millivolts
        if (ADC_Result < 1000){
            GPIOE->ODR &= ~(1UL<<8); //green off
        }
        else if (ADC_Result > 2000){
            GPIOE->ODR |= 1UL<<8; //green on
        }
        LCD_Display_Voltage(ADC_Result);
    }
}

void LCD_Display_Voltage(uint16_t num){
    //Displays number passed to it on LCD screen
    uint8_t digit;
    char i;
    for(i = 0; i < 4; i++){
        digit = num % 10 + 48;
        LCD_WriteChar(&digit, 0, 0, 3-i);
        num /= 10;
    }
    digit = 'm';
    LCD_WriteChar(&digit, 0, 0, 4);
    digit = 'V';
    LCD_WriteChar(&digit, 0, 0, 5);
    return;
}
