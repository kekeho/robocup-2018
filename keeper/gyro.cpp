#include"gyro.hpp"

Gyro::Gyro(){
    correction=0;
    gz=0;
    pregz=0;
    deg=0;
}

void Gyro::init(){
    int count=0;

    Wire.begin();

    gyro.setWire(&Wire);
    gyro.beginGyro();

    int time=millis();
    while (millis()<time+1000){
        gyro.gyroUpdate();
        correction += gyro.gyroZ();
        count++;
    }
    correction/=count;
}

float Gyro::update(float dt){
    gyro.gyroUpdate();
    gz=gyro.gyroZ();

    deg+=(pregz+gz-correction)*dt/2;
    pregz=gz-correction;

    return deg;
}

int Gyro::get_dir(){
    int dir;

    if(deg>2.5){
        dir=100;
    }else if(deg<-2.5){
        dir=-100;
    }else{
        dir=0;
    }

    return dir;
}