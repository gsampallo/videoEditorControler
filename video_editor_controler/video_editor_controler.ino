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

unsigned long lastDebounceTime = 0; 
int ciclo = 0;
int leds[] = { 5,6,9,10 };
unsigned long debounceDelay = 10;
boolean direccion = true;

unsigned long lastIluminarTime = 0; 
unsigned long iluminarDelay = 2500;

boolean iluminar = true;

void setup() {
  /*
  pinMode(pinLed1,OUTPUT);
  pinMode(pinLed2,OUTPUT);
  pinMode(pinLed3,OUTPUT);
  pinMode(pinLed4,OUTPUT); 
  */
  //Serial.begin(9600);
  //todosEncendidos();
  lastDebounceTime = millis();
  efectoEncendido();
}

void efectoEncendido() {
  for(int v=254;v>0;v--) {
    for(int i=0;i<4;i++) {
      analogWrite(leds[i], v);
    }
    delay(10);
  }  
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
    lastIluminarTime = millis();
    iluminar = false;
    ciclo = 254;
    for(int i=0;i<4;i++) {
      analogWrite(leds[i], 254);
    }
    
    if(result == DIR_CW) {
      izquierda();
    } else {
      derecha();
    }

    //Serial.println(result == DIR_CW ? "Right" : "Left");
  }
  //ledCiclo();
  if ((millis() - lastIluminarTime) > iluminarDelay) {
    iluminar = true;
  }
  if(iluminar) {
    variarIntensidad();
  }
}


void ledCiclo() {
  
  if(ciclo >0) {
    ciclo = 0;
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();
    for(int i=0;i<4;i++) {
      if(i == ciclo) {  
        digitalWrite(leds[i], HIGH);
      } else {
        digitalWrite(leds[i], LOW);
      }
    }
    ciclo++;
  }
  
}

void variarIntensidad() {

  if ((millis() - lastDebounceTime) > debounceDelay) {
    lastDebounceTime = millis();  
    
    for(int i=0;i<4;i++) {
      analogWrite(leds[i], ciclo);
    }
    
    //analogWrite(5, ciclo);
    //ciclo++;
    if(ciclo > 254) {
      direccion = true;
    } else if(ciclo == 0) {
      direccion = false;
    }

    if(direccion) {
      ciclo--;
    } else {
      ciclo++;
    }
  }
  
}

void derecha() {
  BootKeyboard.begin();
  //BootKeyboard.write(KEY_DOWN_ARROW);
  //BootKeyboard.write(KEY_PAGE_DOWN);
  BootKeyboard.write(KEY_RIGHT);
  BootKeyboard.releaseAll();
  BootKeyboard.end();
  delay(5);
}

void izquierda() {
  BootKeyboard.begin();
  //BootKeyboard.write(KEY_UP_ARROW);
  //BootKeyboard.write(KEY_PAGE_UP);
  BootKeyboard.write(KEY_LEFT);
  BootKeyboard.releaseAll();
  BootKeyboard.end();  
  delay(5);
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
