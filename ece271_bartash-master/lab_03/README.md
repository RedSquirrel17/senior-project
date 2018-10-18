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

Pre-lab Questions
------- 
1. How to change the rotation speed of a stepper motor?
- To change the rotation speed of the stepper motor, we must change the step frequency. The stepper motor rotates as the magnet is attracted
to different parts of armature of the electromagnets, as the different armature pairs (horizontal vs. vertical) are de-energized and energized
in turn. The faster this happens, the faster the rotation speed. To do this in code, we would want a counter that applies a voltage to the 
pins associated with the pulsing that happens when the armature pairs are de-energized and energized. Increasing the counter would decrease 
the delay between pulses and would then increase the rotation speed. To decrease the speed, we would want to decrease the counter, which 
means that it would have to be set high initially.

2. How to reverse the rotation direction?
- To reverse the rotation direction, we would have to engage the current in the opposite direction. Doing such would require an alternate function
which has the opposite pulse pattern. 

What is your something cool?
-------
For this lab I have programmed by stepper motor to have four different options for motor direction and degree turning, accessible by using the 
joy stick. The up arrow makes the motor turn 360 degrees clockwise, the down arrow makes it turn 360 counterclockwise, the left arrow turns the
motor 180 degrees clockwise and the right arrow turns it 180 degrees counterclockwise. Also, before the motor starts turning, the direction and
degree of turn will flash on the LCD. 


Post-lab Questions
-------
1. The Darlington array has only 500-mA rated collector current. If you need a larger current, what option do you have to replace the Darlington array? 
- A high current MOSFET driver by STMicroelectronics is another option for a high current driver, datasheet here:
http://www.st.com/content/ccc/resource/technical/document/datasheet/38/c6/89/9f/ca/da/45/a3/CD00168777.pdf/files/CD00168777.pdf/jcr:content/translations/en.CD00168777.pdf

2. The full-stepping control sequence rotates a stepper motor a full step for each input pulse. The half-stepping rotates the motor 1/2 step for each
input pulse. Is it possible to rotate the motor 1/4 or 1/8 step for each input pulse?
- Yes. In addition to the full-stepping and half-stepping control sequences, the stepper motor can also be rotated by wave stepping (less refined 
rotation) and micro-stepping (more refined rotation). As we know, full-stepping and half-stepping can result in a motor that has jerky or noisy
movements. Micro-stepping divides a full step into multiple smaller steps, rotating the motor a fraction of a full step in one excitation (fractions
including 1/4, 1/8, 1/16, or 1/32 of a full step). We would use a PWM to do such. The goal of micro-stepping is to adjust the electrical current dynamically
in each winding to make the acceleration or deceleration of the shaft less noticable.

Suggestions and Comments
-------
* Report the typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2017/ece271/home)
* I offer one dollar each new typo or error in the latest edition (printed in May, 2016).

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
Yes, from Andrew Johnson (and Nick Aiken if he helps me with this post lab).
