/*
 * Final Project
 * Steven Mike & Brian Mann
 * Implementation for Key class
 */

#include <iostream>
#include "DoorKey.h"
using namespace std;

//constructor
DoorKey::DoorKey(int t,int x,int y){

	type = t;
	xpos = x;
	ypos = y;
	picked = 0;
}

//returns the type of key
int DoorKey::getType(){

	return type;
}

//returns x position
int DoorKey::getX(){

	return xpos;
}

//returns y position
int DoorKey::getY(){

	return ypos;
}

//returns picked
bool DoorKey::pickedUp(){

	return picked;
}

//sets pick
void DoorKey::setPicked(bool up){
	
	picked=up;
}
