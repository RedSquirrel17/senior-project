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

Pre-lab Assignment
-------
Part 1: Measure the period of 1 Hz square signal

For Timer 4, the clock pre-scaler register (PSC), the compare/capture register (CCR), and the timer free-run counter have 16 bits. 
Thus, their value is limited to 2^16 - 1 = 65535.

Timer Input Clock Frequency: 16MHz

1. Select your timer prescaler (PSC)
- PSC = 15999 (so that the frequency of the  Timer Clock would be 1kHz)

2. If both rising and fall edges of an external signal are selected as active transition, the time internal between two consecutive 
timer interrupts is 0.5 second. What should be the difference of CCR values in two consecutive timer interrupts? Show your calculation.
- x = 500 = 0.5s * 1kHz

3. For the prescaler you have selected, how long (in terms of seconds) after reset a counter overflow or underflow event occurs? Show 
your calculation.
- 65.535s = 65535 / 1k

4. If a counter overflow/underflow occurs, the difference of two CCR readings may not correctly measure the time interval. Explain why 
and how to solve it? (Hints: In the timer interrupt service routine, check the UIF flag)
- This may happen when the reading does not start at zero, the CCR will update, but the flag will not tell you the updates, you will have
to check it. 

Part 2: Interface with Ultrasonic distance sensor

PSC is selected as 15.

1. What is time resolution (minimum time unit) of the input capture function?
- 1 us = 1 / 1MHz

2. If the echo signal is high for time duration from 150us to 38ms, what is the min and max value difference of CCR values in two 
consecutive interrupts?
- min value difference: 150, max value difference: 38000

3. For the prescaler you have selected, how long (in terms of seconds) after reset a counter overflow or underflow event occurs? Show 
your calculation.
- 0.004096s = 65535 / 16M

What is your something cool?
-------
For Part 1 of the lab, the value of the frequency was displayed on the LCD of the board, and for Part 2, the value read by the sensor, which was 
the distance of an object to the sensor in centimeters, was displayed on the LCD. 

Post-lab Questions
-------
1. Does the timer counter count up or down in your lab? If it counts up, how did you handle the counter overflow? (If it counts down, 
how did you handle the counter underflow?)
- This timer counter counts up in my lab. To handle the counter overflow, in my Timer 4 IRQ Handler function I simply kept track of the overflows
by having an integer defined that incremented if the update flag was set, then I cleared the update flag. 

2. What is the accuracy when measuring the period of 1Hz square wave?
- In my code, I had that a 1 Hz signal would be displayed as 1000 on my LCD. When I went to actually measure the period, my LCD display 1002. This means
that there was a 0.2% between my measured and expected values.

3. What is the accuracy of the distance you have measured?
- Measuring distance with the ultrasonic sensor gave fairly accurate results. For close ranges, as in what I could measure with my foot long ruler, the
display usually gave a distance that was within 1 cm of the distance I measured myself. With slightly longer ranges, such as the height of a table or the distance
to a wall, these may have been off by 2 cm. 

4. What is the most challenge issue you had in this lab?
- This lab had a lot of pieces to it, and the mistakes I made in my code were usually small so troubleshooting was difficult at times.

Suggestions and Comments
-------
* Report the typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2017/ece271/home)
* I offer one dollar each new typo or error in the latest edition (printed in May, 2016).

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
- Yes, I recieved a little bit of help from Patrick Roy and Nick Aiken, though I got most of my help from Kent and Nikki.