//keeper
#include "capture.hpp"
#include "move.h"
#include "gyro.hpp"
#include "Sonic.hpp"
#include"line.h"

int UNDEFINED = 0;

Move m;
Gyro gyro;
Capture cap;
Sonic sonic;
Line line(45,100);
Point goalpos;
int i;
int x,y,dir;
bool isthere_mine_goal = true; //ゴールが見えているか
bool isthis_neutral_point = false; //中立点に置かれているかどうか
bool isthere_ball = true; //ボールが見えているか
// PixyI2C pixy(0x55); // You can set the I2C address through PixyI2C object 

void setup(){
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  m.moter_set();
  gyro.init();
  cap.init();

  i=0;

  digitalWrite(13,LOW);
  Serial.begin(9600); //debug
}

void loop() {
  i++;
  y=0;
  gyro.update(0.001);
  dir=gyro.get_dir(); // 方向

  if(i%25==0){
    cap.update();
    x=cap.get_ball(); //ボールのx座標
    goalpos=cap.get_goal(); //自機からみたゴールの座標
    isthere_mine_goal = cap.isthere_mine_goal();
    isthis_neutral_point = cap.isthis_neutral_point();
    isthere_ball = cap.isthere_ball();
  }
  if(sonic.ldist()&&x<0){
    x*=-1;
  }
  if(sonic.rdist()&&x>0){
    x*=-1;
  }

  //ボールを見失ったら
  if(isthere_ball == false && (-20 < goalpos.x && goalpos.x < 20)){
    if(goalpos.x < 0) {
      x = 80;
    } else {
      x = -80;
    }
  }

  //ゴールが見えない場合、とりあえず後ろに戻る
  if(isthere_mine_goal == false){
    y = -100;
  } else if(isthis_neutral_point == true){
    //中立点にいた場合。すぐ後退してゴールに戻る
    y = -100;
  }

  // if(line.check_black()&&sonic.bdist()){
  //   if(line.check_white()){
  //     y=-100;
  //   }
  // }
  if((!line.check_black()&&sonic.bdist())||!line.check_white()){
    y=80;
  }

  m.outPut(dir,x,y);
}