/*
 * Final Project
 * Steven Mike & Brian Mann
 * Implementation of Enemy2 Class
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
#include "Enemy2.h"
using namespace std;

//constructor
Enemy::Enemy(){
    xposition=5;
    yposition=5;
    movementspeed=1;
    attackdamage=1;
    attackrange=2.5;
    visionrange=10;
}

int Enemy::attack(){
    return attackdamage;
}
int Enemy::pursue(int distance,int xpos,int ypos){
    // update x and y positions to follow
    if(distance>0){



    }else if(distance<0){



    }
    if(abs(distance<=1)){
        return attack();
    }else{
        return 0;
    }
}
void Enemy::sound(){
    // play sound
}
int Enemy::getenemyX(){
    return xposition;
}
int Enemy::getenemyY(){
    return yposition;
}
void Enemy::setenemyX(int Xposition){
    xposition = Xposition;
}
void Enemy::setenemyY(int Yposition){
    yposition = Yposition;
}
char Enemy::openDoor(){
    return 'e';
}
