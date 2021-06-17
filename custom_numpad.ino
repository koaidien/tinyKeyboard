#include "DigiKeyboard.h";
#include <Adafruit_NeoPixel.h>

// these defines is incorrect for now
#define RK_0 16384
#define RK_1 16385
#define RK_2 16386
#define RK_3 16387
#define RK_4 16388
#define RK_5 16389
#define RK_6 16390
#define RK_7 16391
#define RK_8 16392
#define RK_9 16393

#define RK_10 16394
#define RK_11 16395
#define RK_12 16396
#define RK_13 16397
#define RK_14 16398
#define RK_15 16399
#define RK_16 16400
#define RK_17 16401
#define RK_18 16402
#define RK_19 16403

const byte pinKM[] = {1,2,3,4,5};  // four pins to Keyboard Matrix
const byte pinLED = 0; // using PWM0
const byte lenLED = 1; // define later

Adafruit_NeoPixel strip = Adafruit_NeoPixel(lenLED, pinLED, NEO_GRB + NEO_KHZ800);

void setup(void)
{
  strip.begin();
  strip.setBrightness(25);  // Lower brightness and save eyeballs!
  strip.show();
}

void loop(void) {
  strip.setPixelColor(0, strip.Color(0,0,0));
  delay(100);
  strip.setPixelColor(0, strip.Color(255,0,0));
  delay(100);
  
  char c = ReadKey();
  DigiKeyboard.println(c);
}

// -------------------  ReadKey ------------------- 
// wait for a key to be pressed
char ReadKey(void) {
  char c;
  short r;

  unsigned long ti=millis()+2000;              // simple autorepeat
  while (0!=ReadKeyboardRaw() && ti>millis());  // wait for previeus key to be unpressed..

  do {
    while (0==(r=ReadKeyboardRaw()));
    delay(10);
  } 
  while( r!=ReadKeyboardRaw() );
  switch(r) {
    case RK_0: c = '0'; break;
    case RK_1: c = '1'; break;
    case RK_2: c = '2'; break;
    case RK_3: c = '3'; break;
    case RK_4: c = '4'; break;
    case RK_5: c = '5'; break;
    case RK_6: c = '6'; break;
    case RK_7: c = '7'; break;
    case RK_8: c = '8'; break;
    case RK_9: c = '9'; break; 
    case RK_10: c = 'A'; break;
    case RK_11: c = 'B'; break;
    case RK_12: c = 'C'; break;
    case RK_13: c = 'D'; break;
    case RK_14: c = 'E'; break;
    case RK_15: c = 'F'; break;
    case RK_16: c = 'G'; break;
    case RK_17: c = 'H'; break;
    case RK_18: c = 'I'; break;
    case RK_19: c = 'K'; break;
    default: c = '?';
  }
  return c;
}

// -------------------  ReadKeyboardRaw ------------------- 
short ReadKeyboardRaw(void) {
  short rawkey=0;
  
  for(byte i=0;i<5;i++) {
// setup ports..    
    for(byte j=0;j<5;j++) {
      if (i==j) {    // output '0'
        pinMode(pinKM[j], OUTPUT);              
        digitalWrite( pinKM[j], LOW);            
      } 
      else { // input 
        pinMode(pinKM[j], INPUT);                          
        digitalWrite( pinKM[j], HIGH);                                      
      }
    }
    delay(1);
// read ports..    
    for(byte j=0;j<5;j++) {
      if (i!=j) {
        if (LOW==digitalRead(pinKM[j])) {
          bitSet(rawkey, j);                                    
        }
      } 
    }
    if (rawkey!=0x0) {  // key pressed, return key
      bitSet(rawkey, i+5);
      break; //return rawkey;      
    } 
  }
  return rawkey;
}
