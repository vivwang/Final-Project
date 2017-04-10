# Final-Project
#### Hugging Pillow with pulse sensor

## Part 1- Hugging Pillow
### Description  
A pillow activated by data collected from pulse sensor wirelessly. When activated, Hugging pillow will open arms, activate a breathing light that listens to you, can record your voice, play pre-recorded sympathy messages from friends and family, also play pre-recorded live-music from people.
 
### Components
* Pillow with hands
* 2 servo motors connected through xBee 
* Servos can turn to a certain degree
* Servo attach to a lever to rotate the arm
* Platform inside pillow to support all components
### Code
* pulse sensor √
* connect 2 motors √
* connect xBee
* pulse sensor moves motors √
* Pulse sensor moves motors only when state changes √
* Pulse sensor activate light
* Pulse sensor activate light when state changes
 

## Part 2- Pulse Sensor
### Description 
Make into a wearable device to collect heart rate

### Components
* Pulse Sensor
* Connect with xBee
* print heart rate
* state != last state
* Wearable component


## Part 3- Activating light 
### Description 
Breathing light to indicate the pillow listens to you. 

### Components
* Light
* Connect with xBee
* Light reacts to voice volumn
* Light activates when ( current state != last state && heart rate= HIGH)
* Light dims when (current state != last state && heart rate= LOW)


## Part 4- Activating speaker
### Description 
Speaker to play pre-recorded voice.

### Components
* speaker activates when (state != last state && heart rate= HIGH)
* play voice
 
