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
I configured the joystick to do more than just toggle when the center was pressed. Now the left arrow sections turns the left LED on, 
the right arrow turns the right LED on, the up arrow turns the left LED off and the down arrow turns the right LED off.

Post-lab Questions
-------
Explain briefly how the hardware debouncing circuit works. Find out a typical solution for software debouncing.

Hardware debouncing in a circuit is generally done by placing a capacitor in parallel with the button that is being pressed. This is because in
pressing a button, in the case of this lab the joy stick, that button can bounce back and force before managing to settle down. This is 
problematic because it results in multiple signals being generated as the button is pressed. By using a capacitor, such bounces and multiple
signals will not occur because a capacitor is meant to resist sudden changes in current, and will turn an AC signal into a clean and easy to deal
with DC signal. In this way, the capacitor will remove the bounces that come with the button pressing. While hardware debouncing is a simple 
matter of adding a single component to a circuit, software debouncing may also be used and a quick snippet of code is all that it requires. 
A simple small delay in a while loop can allow the circuit to give a sort of pause during the switch transition and get rid of the bounces, 
allowing for more accurate results, especially in this case where we cannot easily modify our circuit.

Suggestions and Comments
-------
* Report the typos, errors, or suggestions into the "typos" session on piazza site (https://piazza.com/maine/spring2017/ece271/home)
* I offer one dollar each new typo or error in the latest edition (printed in May, 2016).

Lab Credits
-------
* Did you received any help from someone other than Prof. Zhu and lab teaching assistants?
Yes, Reed Gordon and Nick Aiken helped me with the code for this lab.
