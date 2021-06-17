#include "DigiKeyboard.h"

const byte pinKM[] = {0,1,2,3,4}; // 5 pins for 20 buttons
const byte pinLED = 6; // LED strip maybe

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if( ButtonIn(0, 1)){
    DigiKeyboard.print("0");
  }
  delay(10);
}

bool ButtonIn(int vin, int gnd) {
  pinMode(vin, OUTPUT);  
  pinMode(gnd, INPUT);              
  digitalWrite(vin, HIGH);                           
  digitalWrite(gnd, LOW);   
  delay(1);
  return HIGH==digitalRead(gnd);
}
