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
I used the LCD to aid in the understanding of what was going on in the lab. For part 1, the voltage, either 0V, 1V, 2V, or 3V is displayed on the LCD as the 
potentiometer changes the voltage. For part 2, the LCD as well as the LED indicate when my hand is close to the sensor. When it is not, the LCD spells out
"NAHBRO" and when it is, the LCD spells out "ENOUGH."

Post-lab Questions
-------
1. For 12-bit ADC, we know that ADC Result = floor(2^12 * (V / Vref) + 1/2). Design an experiment to find out Vref.
- To do this, we will use the potentiometer because we know that the reference voltage must be less than the supply voltage of the potentiometer. Knowing the 
voltage range of the pot, 0V-5V, we can keep track of the DigitalValue and turn the pot when this is the maximum threshold, for this case, with a 12-bit ADC, this
is 4095, or 2^12 - 1. When we have turned the pot to achieve this threshold value, we can measure the voltage of the pot output using a digital voltmeter. We 
measured this to be 3.1V.

2. When the voltage output from the potentiometer-based voltage divider is lower than 1.0V, the LED is turned off. What constant value 
should the ADC DR register be compared with?
- DigitalValue = (Voltage Output * 4095) / 3.1 
- The DigitalValue is around 1320. 

3. When the voltage output from the potentiometer-based voltage divider is higher than 2.0V, the LED is light up. What constant value 
should the ADC DR register be compared with?
- The DigitalValue is around 2642.

4. What is the maximum distance at which your sensor can reliably detect your hand?
- It is very small, probably around 1 cm, but on some loads it is further than others. This is due to the quality of the sensor, and could be changed by changing the 
the threshold value in the if statement or the resistor values to drive more current. 

5. What are your comments to ECE 271 (textbook, lectures, labs, exams, anything related)?
- I think that this class is very important but also very difficult, especially for EE majors. For many of us, the first exposure to coding that we have is in 177, 
and then we go the entire summer and a next semester without any more practice. While it might be beneficial to have 271 closer to 177, that would also be difficult
as first semester sophomore year is when we need to take 210, which is also obviously a high demand class. The textbook was not always as helpful because of the board,
but that is going to be remedied very soon. It is sometimes difficult in lecture because we want to review, but it is not always easy to follow up with the lecture 
slides. I do think that you are a fair grader on exams, and we definitely appreciate that, however exam 2 seemed to be very different from exam 1, just looking at 
the types of questions that were asked. I realize that the material for exam 1 was also very different from exam 2, but this fact did throw me for a loop in exam 2. 
In labs, I really wish there were more TAs. I understand that finding students to be TAs is difficult, but one major reason for that is because it is junior year. Is
there any possibility that some seniors would have some spare time to TA? It is just difficult to be productive in lab if we cannot ask questions.

A decent amount of these comments came from class on Friday, but I do think that they are very good points. Hopefully this helps!

Suggestions and Comments
-------
* Report the typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2017/ece271/home)
* I offer one dollar each new typo or error in the latest edition (printed in May, 2016).

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
