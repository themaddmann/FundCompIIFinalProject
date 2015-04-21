// Driver class for Door.h
// Brian Mann and Steven Mike
// 4/11/15
// Door.cpp

#include <iostream>
#include <vector>
#include "Door.h"
#include "DoorKey.h"
using namespace std;

//constructor for the door class
Door::Door(int locked, int hole, int x, int y){
	
	open = 0;
	lock = locked;
	keyhole = hole;
	xpos = x;
	ypos = y;

}

//determines if the door is open or not
int Door::isOpen(){
    
	return open;
}

//determines if the door is locked or not
int Door::isLocked(){
   
	return lock;
}

//sets the door to be locked or not
void Door::setLock(int l){

	lock = l;
}

//opens or closes the door based on its state
void Door::interact(int keys[7]){

	if(lock){
		//see if required key is in invetory
		if(keys[keyhole-1]>0){
			keys[keyhole-1]--;
			lock = 0;
		}
	}

	
	if (! lock) open=1 ;
}

//returns the keyhole
int Door::getType(){

	return keyhole;
}

//returns x position
int Door::getX(){

	return xpos;
}

//returns y position
int Door::getY(){

	return ypos;
}
