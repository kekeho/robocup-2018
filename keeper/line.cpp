#include "Arduino.h"
#include "line.h"

Line::Line(int thb,int thw){
    pinMode(A9,INPUT);
    pinMode(A8,INPUT);
    pinMode(A7,INPUT);
    pinMode(A6,INPUT);

    fpin[0] = A9;
    fpin[1] = A8;
    fpin[2] = A7;
    fpin[3] = A6;

    threshold_black=thb;
    threshold_white=thw;
}

bool Line::check_black(){  
  bool reaction = 0;
  for(int i = 0; i < 4; i++){
    if(analogRead(fpin[i]) < threshold_black){
        reaction = reaction | 1;
    }
  }

  return reaction;
}

bool Line::check_white(){  
  bool reaction = 0;

  for(int i = 0; i < 5; i++){
    if(analogRead(bpin[0][i]) < threshold_white){
        reaction = reaction | 1;
    }
  }

  for(int i = 0; i < 5; i++){
    if(analogRead(bpin[1][i]) < threshold_white){
        reaction = reaction | 1;
    }
  }

  return reaction;
}