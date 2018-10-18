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
I configured the joy stick so when I press the left arrow, the contrast is set to low and when I press the right arrow, the contrast is 
set to high. Initially, when I press the center of the joy stick, the contrast is set to medium. I can change whether the LCD displays my 
name or the given string by slightly modifying the code, changing what is commented out in the main function.


Post-lab Questions
-------
1. Suppose the duty ratio of a LCD display is 1/4 and it has a total of 120 display segments (pixels). How many pins are required to drive 
this LCD?
- On an LCD display, not every display segment requires its own individual to control it. With this LCD display, four COM terminals are used
in different ways to turn the LCD on, or at least to make it look like it is on. Thanks to the 1/4 duty cycle, only 1/4 the number of pins is
required to work the 120 pixels, plus the pins required to work the COM terminals. In total that is 34 pins required to drive this LCD.

2. Can a GPIO pin perform all alternative functions simultaneously?
- No, it cannot. A GPIO pin can be programmed as one of four different functions (digital input, digital output, digital-to-analog or analog-
to-digital conversion, or alternate functions (AF). As determined by the manufacturer, each pin has multiple AF that is able to be programmed
to do, but only one can be set to memory at a time.

3. Is the LCD driver (programmed in this lab) built in within the processor chip? What is the function of the COM driver and SEG driver?
- Yes, the LCD driver is built within the processor chip. The COM driver and the SEG driver are programmed so that the COM pins are able to
control four different segments, the one for a given program determined by which SEG pin is enabled. These pins are programmed so that the
MODE value is 10 and the alternate function value is 0x0B for this lab.

4. How many pixels can the STM32L4 processor LCD driver drive? How large is the LCD_RAM in terms of bits?
- Accoring to the STM32L4 Reference Manual, "The LCD controller is a digital controller/driver for monochrome passive liquid crystal display 
(LCD) with up to 8 common terminals and up to 44 segment terminals to drive 176 (44x4) or 320 (40x8) LCD picture elements (pixels)." The LCD_RAM 
is 32x16 or 512 bits.

5. How many pixels does the LCD installed on the STM32L4 discovery kit have? Explain why many LCD_RAM bits are not used for this LCD.
- The LCD has 96 pixels (which go hand in hand with segments) installed on the STM32L4 discovery kit. Here there are the 96 pixels present, and 
320 pixels not being driven by the driver, which explains why many LCD_RAM bits are not used for this LCD.

Suggestions and Comments
-------
* Report the typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2017/ece271/home)
* I offer one dollar each new typo or error in the latest edition (printed in May, 2016).

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
Yes, Nick Aiken, Reed Gordon, and Ashley Pezanowski also helped me with this lab.
