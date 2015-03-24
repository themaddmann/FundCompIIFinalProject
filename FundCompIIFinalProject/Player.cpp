/*
 * Final Project
 * Steven Mike & Brian Mann
 * Implementation of Player Class
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
#include "Player.h"
using namespace std;

//constructor
Player::Player(){
        xpos=0;
        ypos=0;
        health=3;
        speed=1;
        angle=0;
        running=0;
}

//moves the player
void Player::move(){

        xpos += speed * cos(angle * 3.141592 / 180);
        ypos += speed * sin(angle * 3.141592 / 180);
}

//makes the player run by changing the speed
void Player::run(){

        if (running){
                speed = speed/2;
                running=0;
        }
        else {
                speed = speed*2;
                running=1;
        }
}

//getter and setter functions
double Player::getX(){

        return xpos;
}

double Player::getY(){

        return ypos;
}

int Player::getHealth(){

        return health;
}

void Player::setX(double newX){

        xpos = newX;
}

void Player::setY(double newY){

        ypos = newY;
}

void Player::setHealth(int newHealth){

        health = newHealth;
}
