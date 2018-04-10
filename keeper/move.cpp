#include "Arduino.h"
#include "move.h"

void Move::moter_set(){
  pinMode(37, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  
  pinMode(4, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  
  pinMode(8, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(29, INPUT);
}

void Move::outPut(float angle, float x, float y){
  bool a;
  sw = digitalRead(29); 
  out1 = (1/3.0)*x + (1/sqrt(3))*y - (r/3.0)*angle;
  out2 = (1/3.0)*x - (1/sqrt(3))*y - (r/3.0)*angle;
  out3 = -(2/3.0)*x - (r/3.0)*angle;
  
  if(out2 > 0){
    a = 1;
  }else{
    a = 0;
  }
  analogWrite(36, abs(out2)*sw);
  digitalWrite(35, (a+1)%2);
  digitalWrite(37, a);
//  Serial.print(out1);
//  Serial.print(" ");
//  Serial.print(sw);
//  Serial.print(" ");
//  Serial.print((a+1)%2);
//  Serial.print(" ");
//  Serial.println(a);
  if(out3 > 0){
    a = 1;
  }else{
    a = 0;
  }
  analogWrite(3, abs(out3)*sw*0.75);
  digitalWrite(2, (a+1)%2);
  digitalWrite(4, a);

  if(out1 > 0){
    a = 1;
  }else{
    a = 0;
  }
  analogWrite(9, abs(out1)*sw);
  digitalWrite(8, (a+1)%2);
  digitalWrite(10, a);
//    analogWrite(Pwm, coefficient*abs(value)*digitalRead(sw));
//    digitalWrite(outA, (a+1)%2);
//    digitalWrite(outB, a);
//    //digitalWrite(outB, (abs(value) - value)/(2*value));
    // Serial.print(out1);
    // Serial.print(" ");
    // Serial.print(out2);
    // Serial.print(" ");
    // Serial.println(out3);
}
  
