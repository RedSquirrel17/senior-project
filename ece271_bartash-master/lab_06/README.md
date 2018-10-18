ECE 271 - Microcomputer Architecture and Applications  
Lab Report  
Spring 2017     


Name
-----------
```
Bailee Bartash
```

Summary of Lab Status
-------
- [ ] Pre-lab Assignment  
- [ ] Incomplete task  
    - [ ] Sub-task 1:   
    - [ ] Sub-task 2:   
    - [ ] Sub-task 3:   

What is your something cool?
-------
See below.

Post-lab Questions
-------
1. What is your something cool?
- I used the delay function to send out a Morse code message of "HI KENT" (.... ..  -.- . -. -) because Kent is my TA via the LED light. There
is a 1/4 pause between letters and 1/2 second pause between words. 

Because I was having difficulty getting the LED to flash exactly as I wanted, there is also code to send out a Morse code message for "SOS." The
more complex code was written after I figured out the SOS flash sequence.

2. As shown in the lab handout, Cortex-M supports up to 256 interrupts. What is the interrupt number of the SysTick defined in CMSIS?
- By searching for the interrupt number in the stm32l476xx.h file of my Lab 6 code, I found the definitions of Cortex-M4 Processor Exception
Numbers and by SysTick_IRQn = -1 the comments said that the associated interrupt number was 15 as defined by CMSIS.

3. What is the default interrupt priority of SysTick? Does a higher priority value represent a higher urgency?
- Looking at the STM32L476 Reference Manual I found that the priority was defined as 6, while we set the associated priority level to 240. Here
the larger the number, the lower the urgency.

4. Is the SysTick interrupt enabled by default?
- No, we had to enable it in our code, setting the SysTick control register to 0. 

5. Suppose a clock of 16MHz is used to drive the system timer. What is the maximum interval between two consecutive SysTick interrupts
we can possibly obtain?
- We can calculate the SysTick Interrupt Period = (1 + SysTick_LOAD) * (1 / (SysTick Counter CLock Frequency))
Since the maximum possible value for the SysTick interrupt register is 24 bits (2^24) we have (1 + (2^24)) / 16M) = 1.049s. Also, because SysTick 
is fixed to be a 24-bit down counter, slowing the clock frequency will increase the maximum interval between two consecutive interrupts.

Suggestions and Comments
-------
* Report the typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2017/ece271/home)
* I offer one dollar each new typo or error in the latest edition (printed in May, 2016).

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
