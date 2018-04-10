#include"Sonic.hpp"

Sonic::Sonic(){
    pinMode(5,INPUT);
    pinMode(6,INPUT);
    pinMode(7,INPUT);
}

int Sonic::ldist(){
    return digitalRead(5);
}

int Sonic::rdist(){
    return digitalRead(6);
}

int Sonic::bdist(){
    return digitalRead(7);
}