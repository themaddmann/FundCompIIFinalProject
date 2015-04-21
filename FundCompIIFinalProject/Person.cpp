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
double Person:: getY(){

	return ypos;
}
