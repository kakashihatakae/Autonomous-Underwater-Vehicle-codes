# Autonomous-Underwater-Vehicle-codes
This repository contains all the codes that I have written in ROS using C++ and python for our Autonomous Underwarer Vehicle project in my undergrad.

In my undergrad I found a club called **Trident Labs**. The main aim of this club was to design and manuacture an autonomous underwater vehicle from scratch and participate in International AUV competitions. I was the overall head and the also the software head of the team. I have written ROS codes to simulate an AUV using the famous **UWsim**. 

There are four packages :-
1. angle_find
2. depth_maintain
3. robot_codes

#### angle_find
This package is responsible to return a heading for the AUV calculated from a marker of a specific colour on the pool floor. 

#### depth_maintain
This package takes inputs from the pressure sensor simulated by UWsim and controls the thrusters to maintain a specific depth using the PID controller.
