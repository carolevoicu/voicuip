#include<SoftwareSerial.h>

/* Create object named bt of the class SoftwareSerial */ 
SoftwareSerial bt(10,9); /* (Rx,Tx) */  
int randHRM, randHum, randTemp, randBPM;
void setup() {
  bt.begin(9600); /* Define baud rate for software serial communication */
}

void loop() {

randHRM=random(300, 500);
randHum=58;
randTemp=26;
randBPM=random(80, 100);
      bt.print(randHRM); /* Print character received on to the serial monitor */
      bt.print("/"); 
      bt.print(randHum); 
      bt.print("/"); 
      bt.print(randTemp); 
      bt.print("/"); 
      bt.print(randBPM);
      bt.println(""); 
      bt.flush();
      delay(500);
}
