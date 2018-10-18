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
I used the PWM to generate a music tone of A, which was a 440-Hz sine wave by changing the prescaler value and deleting the branch to 
my C function that changed the brightness of my green LED. 

Post-lab Questions
-------
1. In order to generate 1 Hz square wave with a duty cycle of 50%, how would set up the timer? Indicate your counting mode and show 
the value of ARR, CRR, and PSC registers.
- Obtaining the 50% duty cycle is quite simple, and the same values for the ARR and CRR are used as in the lab demo. This means that for
this square wave generation, ARR = 199 and CRR = 100. This corresponds to the equation for the duty cycle in PWM mode 1 where
DC = (CRR / (ARR + 1)) * 100%. The PSC register needs to equal 2^16 - 1, so that PSC = 65535 because we need 65535 / 65535 = 1Hz.

2. What is the smallest PWM frequency that can be generated?
- The smallest PWM frequency is actually 1Hz. We know this because the maximum value of the PSC is 2^16 and the frequency that we have 
when the PSC is 2^16 is 1Hz.

3. What suggestions would you give to me? (Anything related to my book, my lectures and my labs. Thank you.)
- Lab is actually a difficult environment to work in and that is one of the reasons that some people leave early. Personally I do prefer 
to stay in lab for the entire three hours, but many others do not and they just end up wasting their time and making the lab noisy. If 
people can work on labs and be more productive outside the lab itself, is it such a bad thing that they do not want to stay?
- Some of the lab demos are actually very extensive and sometimes the TAs do not know how to do them either. Perhaps if there was more
training for the TAs, or possibly videos that could explain things such as last lab and working in the debug environment, I would find that
very beneficial. 

Suggestions and Comments
-------
* Report the typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2017/ece271/home)
* I offer one dollar each new typo or error in the latest edition (printed in May, 2016).

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
Yes, from Nick Aiken.