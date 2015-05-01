/*
 * Final Project
 * Steven Mike & Brian Mann
 * Implementation of Person Class
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Person.h"
using namespace std;

//constructor
Person::Person(){
	xpos=0;
	ypos=0;
	xVel=0;
	yVel=0;
}

//get x position
double Person::getX(){

	return xpos;
}

//get y position
double Person::getY(){

	return ypos;
}

//get xVel
double Person::getXVel(){
	return xVel;
}

//get yVel
double Person::getYVel(){
	return yVel;
}

//set Y Velocity
void Person::setYVel(double y){

	yVel = y;
}

//set X Velocity
void Person::setXVel(double x){

	xVel = x;
}
