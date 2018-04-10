#include"Capture.hpp"

//x:185 y:90::center,left_back::0,0

Capture::Capture(){
    flag=false;
    blocks=0;
    pinMode(30,INPUT);
}

void Capture::init(){
    pixy.init();
}

void Capture::update(){
    blocks = pixy.getBlocks();
}

int Capture::get_ball(){
    int x,i;

    if (blocks) {
        for (i=0; i<blocks; i++) {
            if(pixy.blocks[i].signature==1){
                flag=true;
                if((pixy.blocks[i].x <= 160 || pixy.blocks[i].x >= 200)){
                    x=pixy.blocks[i].x - 180;
                }else{
                    flag=false;
                }
            }else{
                flag=false;
            }
        }
    }else{
        flag=false;
    }

    if(!flag){
        x=0;
    }

    if(x<0){
        return -220;
    }
    if(x>0){
        return 220;
    }

    return 0;
}

Point Capture::get_goal(){
    Point goalpos;
    int i;

    if (blocks) {
        for (i=0; i<blocks; i++) {
            if(pixy.blocks[i].signature==digitalRead(30)+2){
                flag=true;
                if((pixy.blocks[i].x >= 200 || (pixy.blocks[i].x <= 160))){
                    goalpos.x=pixy.blocks[i].x - 180;
                    goalpos.y=pixy.blocks[i].y - 85;
                }else{
                    flag=false;
                }
            }else{
                flag=false;
            }
        }
    }else{
         flag=false;
    }

    if(!flag){
        goalpos.x=0;
        goalpos.y=0;
    }

    return goalpos;
}

bool Capture::isthis_neutral_point(){
    if (blocks) {
        for(int i = 0; i < blocks; i++){
            //味方のゴールが見えている場合
            if(Capture::isthere_mine_goal()) {
                //前にあったら中立点/後ろにあれば中立点ではない
                // Serial.print(pixy.blocks[i].y); Serial.print('\n');
                if(pixy.blocks[i].y < 38){ //TODO: y - 90が必要かもしれない
                    //中立点にいる
                    return true;
                }
            }
        }
    }
    return false;
}

//味方のゴールが見えているか
bool Capture::isthere_mine_goal(){
    if(blocks){
        for(int i = 0; i < blocks; i++){
            //pixyで取得したブロックのシグネチャが色選択スイッチで選択した色と同じだった場合(味方のゴール)
            if(pixy.blocks[i].signature == digitalRead(30)+2){
                // Serial.print(pixy.blocks[i].width); Serial.print('\n'); 
                if(pixy.blocks[i].width < 20){
                    //ノイズと思われるためゴールではないとみなす
                    return false;
                }               
                return true;
            }
        }
    }
    return false;
}

//ボールが見えているか
bool Capture::isthere_ball(){
    if(blocks){
        for(int i; i < blocks; i++){
            //ボールが見つかったぞ!
            if(pixy.blocks[i].signature == 1){
                return true;
            }
        }
    }
    return false;
}