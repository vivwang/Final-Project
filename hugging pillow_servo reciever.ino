#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


int pos = 0;
int incomingByte;
int servoState = 0; // current state of the servo
int lastServoState = 0; // previous state of the button
//int count = 0;


void setup()
{
  Serial.begin(9600);
  myservo.attach(8);  // attaches the servo on pin 9 to the servo object
}

void loop()
{
  //Serial.println(Serial.available());
  while (Serial.available() > 0)
  {

    incomingByte = Serial.parseInt();
    Serial.println(incomingByte);
    if (Serial.read() == '\n')
    {
      Serial.println(incomingByte);


      if (incomingByte == 1 )
      {
        for (pos = 0; pos <= 45; pos += 1)
        {
          myservo.write(pos);
        }
      }
      else if (incomingByte == 2)
      {
        for (pos = 45; pos >= 0; pos -= 1)
        {
          myservo.write(pos);
          delay(15);
        }
      }
    }
  }

}




