/*   
    The circuit:
    * encoder pin A to Arduino pin 4
    * encoder pin B to Arduino pin 3
    * encoder ground pin to ground (GND)
*/

#include <Rotary.h>
#include "HID-Project.h"

Rotary r = Rotary(4,3);
int valor = 0;

int pinLed1 = 5;
int pinLed2 = 6;
int pinLed3 = 9;
int pinLed4 = 10;

void setup() {
  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinLed4,OUTPUT); 
  
  Serial.begin(9600);
  todosEncendidos();
}


void todosEncendidos() {
  digitalWrite(pinLed1, HIGH);
  digitalWrite(pinLed2, HIGH);
  digitalWrite(pinLed3, HIGH);
  digitalWrite(pinLed4, HIGH);
}

void loop() {

  int oldLed = 0;  
  unsigned char result = r.process();
  if (result){
    if(result == DIR_CW) {
      izquierda();
    } else {
      derecha();
    }

    Serial.println(result == DIR_CW ? "Right" : "Left");
  }
}

void derecha() {
  BootKeyboard.begin();
  BootKeyboard.write(KEY_RIGHT_ARROW);
  delay(10);
  BootKeyboard.releaseAll();
  BootKeyboard.end();
}

void izquierda() {
  BootKeyboard.begin();
  BootKeyboard.write(KEY_LEFT_ARROW);
  delay(10);
  BootKeyboard.releaseAll();
  BootKeyboard.end();  
}

void espacio() {
  BootKeyboard.begin();
  BootKeyboard.write(KEY_F5);
  delay(10);
  BootKeyboard.releaseAll();
  BootKeyboard.end();    
}

void subirVolumen() {
  Consumer.begin();
  Consumer.write(MEDIA_VOLUME_UP);
  delay(10);
  Consumer.releaseAll();
  Consumer.end();  

  
}

void bajarVolumen() {
    Consumer.begin();
    Consumer.write(MEDIA_VOLUME_DOWN);
    delay(10);
    Consumer.releaseAll();
    Consumer.end();  
}
