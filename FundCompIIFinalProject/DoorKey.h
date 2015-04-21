/*
 * Final Project 
 * Steven Mike and Brian Mann
 * Interface for Key class
 */
#ifndef DOORKEY_H
#define DOORKEY_H

#include <iostream>
using namespace std;

class DoorKey{
	
	public:
		DoorKey(int,int,int); //constructor
		int getType(); //returns the type of key
		int getX(); //returns xpos
		int getY(); //returns ypos
		bool pickedUp(); //returns picked
		void setPicked(bool); //sets picked
	private:
		int type; //what types of locks the key can open
		int xpos,ypos; //location
		bool picked; //determines if key has been picked up or not
};

#endif
