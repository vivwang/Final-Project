
//  Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int blinkPin = 13;                // pin to blink led at each beat
int fadePin = 5;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
int count_1 = 0;                    // heart beat counter
int count_2 = 0;

// Volatile Variables, used in the interrupt service routine!
volatile int BPM;                   // int that holds raw Analog in 0. updated every 2mS
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // int that holds the time interval between beats! Must be seeded!
volatile boolean Pulse = false;     // "True" when User's live heartbeat is detected. "False" when not a "live beat".
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.


void setup() {
  pinMode(blinkPin, OUTPUT);        // pin that will blink to your heartbeat!
  pinMode(fadePin, OUTPUT);         // pin that will fade to your heartbeat!
  Serial.begin(9600);             // we agree to talk fast!
  interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS
  // IF YOU ARE POWERING The Pulse Sensor AT VOLTAGE LESS THAN THE BOARD VOLTAGE,
  // UN-COMMENT THE NEXT LINE AND APPLY THAT VOLTAGE TO THE A-REF PIN
  //   analogReference(EXTERNAL);
}


//  Where the Magic Happens

void loop() {
  //Serial.print(analogRead(A0));
  delay (2000);
  //sendDataToProcessing('S', Signal);     // send Processing the raw Pulse Sensor data
  if (QS == true) {    // A Heartbeat Was Found
    // BPM and IBI have been Determined
    // Quantified Self "QS" true when arduino finds a heartbeat
    fadeRate = 255;         // Makes the LED Fade Effect Happen
    // Set 'fadeRate' Variable to 255 to fade LED with pulse
    // serialOutputWhenBeatHappens();   // A Beat Happened, Output that to serial.
    //sendDataToProcessing('B', BPM);  // send heart rate with a 'B' prefix
    // Serial.print (BPM);
    //sendDataToProcessing('Q', IBI);  // send time between beats with a 'Q' prefix
    QS = false;           // reset the Quantified Self flag for next time
    if (BPM < 50) {
      Serial.print(2);   // slow
      Serial.print (" ");
      //Serial.print ("count_2 ");
      Serial.print (count_2);
     
      Serial.println();
      count_2 ++;
      delay(1000);
    }
    if (BPM > 50) {
      Serial.print (1);    // fast
      Serial.print (" ");
     //  Serial.print ("count_1 ");
      Serial.print (count_1);
      Serial.println();
      count_1 ++;
      delay (1000);
    }
  }

  ledFadeToBeat();                      // Makes the LED Fade Effect Happen
  delay(200);                             //  take a break
}

void ledFadeToBeat() {
  fadeRate -= 15;                         //  set LED fade value
  fadeRate = constrain(fadeRate, 0, 255); //  keep LED fade value from going into negative numbers!
  analogWrite(fadePin, fadeRate);         //  fade LED
}

void sendDataToProcessing(char symbol, int data ) {
  Serial.print(symbol);                // symbol prefix tells Processing what type of data is coming
  Serial.println(data);                // the data to send culminating in a carriage return

}

// requires recycling the output in the "smoothedVal" param
int smooth(int data, float filterVal, float smoothedVal) {

  if (filterVal > 1) {     // check to make sure param's are within range
    filterVal = .999999;
  }
  else if (filterVal <= 0) {
    filterVal = 0;
  }

  smoothedVal = (data * (1 - filterVal)) + (smoothedVal  *  filterVal);

  return (int)smoothedVal;
}
