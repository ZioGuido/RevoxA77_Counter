# RevoxA77_Counter
Project for an OLED dispay counter for the Revox A77 r2r tape machine

This is a sketch for a simple project that aims to replace the mechanical tape counter of a Revox A77 tape recorder with a digital counter based on an optical encoder and an OLED display.

The display module is a classic 0,96" 128x32 I2C module. The encoder is made by using two IR proximity sensors and two pieces of reflective adhesive tape applied to the take-up reel motor shell.
Since there's nothing else in the cicruit, and all connections are cleary explained in code comments, there's no need to make a circuit schematic. Just connnect the I2C display to GPIOs 2 and 3 (SDA, SCL), the two IR sensors to GPIOs 4 and 5, and a button to GPIO 6. That's all. Then you'll have to find the right position to place the sensors so that the reflective tape is properly "read" at every revolution. 

Here's a short video that pretty much explains it all.
https://www.youtube.com/watch?v=ur7Ue5t6CtI

