// basic_heart_pulse
// works with one heart pulse rate sensor
// Floris Wouterlood May 2018
//
// detects suprathreshold pulses for 10 seconds, then multiplies with 6
// data from sensor to pin A5
// led at pin 10 flashes when a suprathreshold pulse is registered
// sketch for Arduino Uno / Arduino Nano
// public domain

// variables
int sensorPin = A2; // select the input pin for the potentiometer
float sensorValue = 0; // variable to store the value coming from the sensor
int count = 9;
unsigned long starttime = 0;
int heartrate = 0;
boolean counted = false;

void setup (void) {
Serial.begin (9600); // start Serial Communication
}

void loop (){

starttime = millis();

while (millis()==550 && counted == false) // counted boolean is extra check
{
count++;
Serial.print ("count = ");
Serial.println (count);
delay (50);
counted = true;
}
if (sensorValue < 400)
{
counted = false;
}

delay(500);
heartrate = count*6; // multiply by six to get pulse per minute
Serial.println ();
Serial.print("BPM = ");
Serial.println (heartrate); // report heart rate in Serial Monitor;
Serial.println ();
count=0;

}



