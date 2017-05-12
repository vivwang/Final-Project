#include <Servo.h>

Servo myservo1;  // create servo object to control a servo
Servo myservo2;
// twelve servo objects can be created on most boards


int pos = 0;
int incomingByte;
int servoState = 0; // current state of the servo
int lastServoState = 0; // previous state of the button
int count1 = 0; // heart beat counter
int count2 = 0;

const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock;
int ledPin = 11;
int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

boolean sound=false;


void setup()
{
  Serial.begin(9600);
  myservo1.attach(6);  // attaches the servo on pin A0 to the servo object
  myservo2.attach(7);
 pinMode(ledPin, OUTPUT);
}

void loop()
{
   
  //Serial.println(Serial.available());
  while (Serial.available() > 0)
  {

    incomingByte = Serial.parseInt();
    Serial.println(incomingByte);
    count = Serial.parseInt();
    Serial.println(count);

    //if (Serial.read() == '\n')
    //{
     // Serial.println(incomingByte);
     // Serial.println(count);


      if (incomingByte == 1  && count1 > 5  )
      {
        for (pos = 0; pos <= 180; pos += 1)
        {
          myservo1.write(pos);
        }
        for (pos = 180; pos >= 0; pos -= 1)
        {
          myservo2.write(pos);
        }
        count2 = 0;
        
      }
      else if (incomingByte == 2  && count2 > 5  )
      {
       
        //digitalWrite(9, HIGH);
        for (pos = 180; pos >= 0; pos -= 1)
        {
          myservo1.write(pos);
        }
        for (pos = 0; pos <= 180; pos += 1)
        {
          myservo2.write(pos);
        }
        count1 = 0;
         sound=true;
      }

    }
 // }
//if(sound==true){
//soundfade();
//}
}

void soundfade()
{
  unsigned long start = millis(); // Start of sample window
  unsigned int peakToPeak = 0;   // peak-to-peak level

  unsigned int signalMax = 0;
  unsigned int signalMin = 1024;
  unsigned int targetBrightness;

  // collect data for 250 miliseconds
  while (millis() - start < sampleWindow)
  {
    knock = analogRead(0);
    if (knock < 1024)  //This is the max of the 10-bit ADC so this loop will include all readings
    {
      if (knock > signalMax)
      {
        signalMax = knock;  // save just the max levels
      }
      else if (knock < signalMin)
      {
        signalMin = knock;  // save just the min levels
      }
    } else {
      Serial.println("Something is wrong!!!");
      while (true) {
      }
    }
    Serial.println(signalMin);

    peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
    targetBrightness = map (peakToPeak, 80, 1023, 0, 255);

    //targetBrightness = constrain (targetBrightness, 0, 255);
    //  double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
    //  Serial.println(volts);


    // calculate brightness based on target
    if (targetBrightness > brightness) {
      brightness +=  fadeAmount ;
    } else {
      brightness -=  fadeAmount ;
    }
    //  Serial.println(brightness);

    //fade LED
    analogWrite (ledPin, brightness);  // set the brightness of pin;

    //conditional on sound level very quiet
    //  if (brightness == 0 || brightness == 255)
    //  { // reverse the direction of the fading at the ends of the fade:
    //    fadeAmount = -fadeAmount ;
    //  }
    // delay (30);

    Serial.print("Knock: ");
    Serial.print(knock);
    Serial.print("\tMin: ");
    Serial.print(signalMin);
    Serial.print("\tMax: ");
    Serial.print(signalMax);
    Serial.print("\tPeak-to-Peak: ");
    Serial.print(peakToPeak);
    Serial.print("\tTarget Brightness: ");
    Serial.print(targetBrightness);
    Serial.println();
  }

}





