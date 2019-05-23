#include <SoftwareSerial.h>
#include <dht.h>
SoftwareSerial bt(9,3);
dht DHT;
//  if  you require to change the pin number, Edit the pin with your arduino pin.
#define DHT11_PIN 2


int UpperThreshold = 600;
int LowerThreshold = 700;
int reading = 0;
float auxBPM=0;
int HRM=0;
int a=0;
unsigned long duration;
float BPM = 0.0;
bool IgnoreReading = false;
bool FirstPulseDetected = false;
unsigned long FirstPulseTime = 0;
unsigned long SecondPulseTime = 0;
unsigned long PulseInterval = 0;
const unsigned long delayTime = 100;
const unsigned long delayTime2 = 1000;
unsigned long previousMillis = 0;
unsigned long previousMillis2 = 0;


void setup() {
  bt.begin(9600);
  Serial.begin(9600); 
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
}


void loop() {   
    unsigned long currentMillis = millis();
  if((digitalRead(10) == 1)||(digitalRead(11) == 1)){
    HRM=0;
  }
  else{
    // send the value of analog input 0:
      HRM=analogRead(A0);
  }
  
  // First event
  if(myTimer1(delayTime, currentMillis) == 1){
    int chk = DHT.read11(DHT11_PIN);
    reading = analogRead(A2); 

    // Heart beat leading edge detected.
    if(reading > UpperThreshold && IgnoreReading == false){
      if(FirstPulseDetected == false){
        FirstPulseTime = millis();
        FirstPulseDetected = true;
      }
      else{
        SecondPulseTime = millis();
        PulseInterval = SecondPulseTime - FirstPulseTime;
        FirstPulseTime = SecondPulseTime;
      }
      IgnoreReading = true;
    }

    // Heart beat trailing edge detected.
    if(reading < LowerThreshold && IgnoreReading == true){
      IgnoreReading = false;
    }  

    // Calculate Beats Per Minute.
    BPM = (1.0/PulseInterval) * 60 * 1000;
  }

  // Second event
  
  if(myTimer2(delayTime2, currentMillis) == 1){
    if(BPM<120&&BPM>50){
      auxBPM=BPM;
      }
    bt.print(HRM);
    bt.print("/");
    bt.print(DHT.humidity);
    bt.print("/");
    bt.print(DHT.temperature);
    bt.print("/");
    bt.print(auxBPM);
    bt.print("\n");
    bt.flush();
    }
  }
// First event timer
int myTimer1(long delayTime, long currentMillis){
  if(currentMillis - previousMillis >= delayTime){previousMillis = currentMillis;return 1;}
  else{return 0;}
}

// Second event timer
int myTimer2(long delayTime2, long currentMillis){
  if(currentMillis - previousMillis2 >= delayTime2){previousMillis2 = currentMillis;return 1;}
  else{return 0;}
}
    
