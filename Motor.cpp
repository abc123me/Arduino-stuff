#ifndef digitalWrite
#include "Arduino.h"
#endif
#ifndef MOTOR_HEADERS
#include "Motor.h"
#endif

/*--------Pins--------*/
#define enA 9
#define enB 10
#define i1 8
#define i2 11
#define i3 12
#define i4 13
/*--------Misc--------*/
bool motorsEnabled = false;
/*---Getters/Setters---*/
void setMotorsEnabled(bool enabled){
    motorsEnabled = enabled;
    if(!enabled)
        allMotorStop();
}
bool areMotorsEnabled(){
    return motorsEnabled;
}
/*----Motor control----*/
void motorInitiate(){
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(i1, OUTPUT);
  pinMode(i2, OUTPUT);
  pinMode(i3, OUTPUT);
  pinMode(i4, OUTPUT);
  setMotorsEnabled(true);
  allMotorStop();
}
void allMotorStop(){
  digitalWrite(enA, LOW);
  digitalWrite(enB, LOW);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);
}
void motor1Stop(){
  digitalWrite(enA, LOW);
  digitalWrite(i1, LOW);
  digitalWrite(i2, LOW);
}
void motor2Stop(){
  digitalWrite(enB, LOW);
  digitalWrite(i3, LOW);
  digitalWrite(i4, LOW);
}
void motor1Forward(){
  if(!areMotorsEnabled()) return;
  digitalWrite(enA, HIGH);
  digitalWrite(i1, HIGH);
  digitalWrite(i2, LOW);
}
void motor2Forward(){
  if(!areMotorsEnabled()) return;
  digitalWrite(enB, HIGH);
  digitalWrite(i3, LOW);
  digitalWrite(i4, HIGH);
}
void motor1Backward(){
  if(!areMotorsEnabled()) return;
  digitalWrite(enA, HIGH);
  digitalWrite(i1, LOW);
  digitalWrite(i2, HIGH);
}
void motor2Backward(){
  if(!areMotorsEnabled()) return;
  digitalWrite(enB, HIGH);
  digitalWrite(i3, HIGH);
  digitalWrite(i4, LOW);
}
