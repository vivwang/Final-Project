/*
* The Circuit:
* Connect AUD to A0
* Connect GND to GND
* Connect VCC to 5V

*/

const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
unsigned int knock;
int ledPin = 9;
int brightness = 0;    // how bright the LED is
int fadeAmount = 1;    // how many points to fade the LED by

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop()
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
