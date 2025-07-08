Engineering materials
====
This are the material that were used for the development of this project:

1. 3 Car planks	
2. 4 Hex coupler connector	
3. L289N DC motor controller	
4. Screws
5. 3 Sensor carriers	
6. 4 wheels	
7. DC motor	
8. Metal separators
9. 2 Axle carriers	
10. 2 MG996R Servo motor	
11. Plastic separators	
12. Arduino UNO R4	
13. Vex battery



## Introduction

The robot moves using a DC motor controlled by an H-bridge motor driver. It uses three pins, IN1, IN2, and ENA, to set the direction and speed. The move() function allows the robot to go forward or backward, while the stop() function cuts the power to the motor to make it stop. This setup gives the robot basic but effective movement control, allowing it to travel through its environment smoothly.The robot is powered by a VEX 7.2V rechargeable battery. This battery is strong and reliable, designed for student robotics. It can power the motors and the electronics at the same time without losing voltage. The battery is rechargeable, safe, and long-lasting, which makes it perfect for classroom or project use. 


The speed of the motor is controlled using the analogWrite() function on the ENA pin. This uses a method called PWM (pulse width modulation), which lets the robot change speed without turning the motor completely on or off. The code also uses the absolute value of the speed and checks the direction so that negative numbers make the motor move in reverse without causing errors. This makes the robot's movement flexible and safe.

For obstacle detection, the robot uses three VL53L0X Time-of-Flight (ToF) sensors. One is placed in the front, and the others on the left and right sides. These sensors use laser measurements to check how far objects are, allowing the robot to avoid hitting things. The sensors are connected using different I2C addresses and special pins called xshutPins, which makes it possible to use all three at once on an Arduino. The front sensor (Fdist) looks for objects ahead, while the left (Ldist) and right (Rdist) sensors help the robot decide which way to turn.




