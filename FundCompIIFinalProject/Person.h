/*
 * Person base class for Final Project
 * Steven Mike & Brian Mann
 * Players and Enemy will be subclasses
 */

#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Level.h"
using namespace std;

class Person{

	public:
		Person(); //constructor
		virtual void move(Level) = 0; //moves object based on Level information
		double getX(); //returns xposition
		double getY(); //returns yposition
		
	protected:
		double xpos; //xposition
		double ypos; //yposition
		double xVel, yVel; //velocities
};

#endif
