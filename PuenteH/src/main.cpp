#include <Arduino.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include "CWifi.h"
#include<stdio.h>
#include<math.h>

AsyncWebServer server(80);
const int Q1 = 25;
const int Q2 =26;
struct Button {
  const uint8_t PIN;
  uint32_t numberKeyPresses;
  bool pressed;
};
Button button1 = {33, 0, false};
Button button2={32,0,false};
void IRAM_ATTR isr() {
  button1.numberKeyPresses += 1;
  button1.pressed = true;
}
void IRAM_ATTR isr2(){
  button2.pressed=true;
}
float periodo;
void setup() {
  Serial.begin(9600);
  wifi(); //inicilizacion de WiFi
  get_service(); //Inicio servicios para el html y para el post
  pinMode(Q1,OUTPUT);
  pinMode(Q2,OUTPUT);
  pinMode(25,OUTPUT);
  digitalWrite(Q1,LOW);
  digitalWrite(Q2,LOW);
  pinMode(27,OUTPUT);
  pinMode(14,OUTPUT);

  pinMode(button1.PIN, INPUT_PULLUP);
    pinMode(button2.PIN, INPUT_PULLUP);
  
  attachInterrupt(button1.PIN, isr, FALLING);
  attachInterrupt(button2.PIN, isr2, FALLING);
}


void loop() {
  
  periodo=( 1/outputString.toFloat());
 // Serial.println(String(periodo*1000000).toInt());
 // Serial.println(String((periodo*1000000)/2).toInt());
  if(bandera || button1.pressed ){
      button2.pressed = false;
      //Serial.println("1");
      digitalWrite(14,HIGH);
      digitalWrite(27,LOW);
    //
    //Serial.println(outputString);
   // Serial.println(frecuencia);
    digitalWrite(Q1,LOW);
    delayMicroseconds(1);
    digitalWrite(Q2,HIGH);
    if(encendido){
        //Serial.println(outputString2);

    delayMicroseconds(outputString2.toInt());
    }else{
    delayMicroseconds(String((periodo*1000000)/2).toInt());
    }
    digitalWrite(Q2,LOW);
    delayMicroseconds(1);
    digitalWrite(Q1,HIGH);
    if(encendido){
    delayMicroseconds(outputString3.toInt());
     // Serial.println(outputString3);

    }else{
    delayMicroseconds(String((periodo*1000000)/2).toInt());
    }

  }else{
     //Serial.println("stop");
     digitalWrite(Q2,LOW);
     digitalWrite(Q1,LOW);
  }
   if (button2.pressed) {
      button1.pressed = false;
      digitalWrite(14,LOW);
      digitalWrite(27,HIGH);
      bandera=false;
     /// Serial.println("2");
      
  }
  
}

