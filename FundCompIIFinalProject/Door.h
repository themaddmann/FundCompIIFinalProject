// Class for doors
// Brian Mann and Steven Mike
// 4/11/15
// Door.h

#ifndef DOOR_H
#define DOOR_H

#include <iostream>
#include "DoorKey.h"
using namespace std;

class Door{
    public:
        Door(int,int,int,int); //constructor
        int isOpen(); //returns open
        int isLocked(); //returns lock
	int getType(); //returns keyhole
	void setLock(int); //sets lock
	void interact(int[7]); //opens or closes the door based on its state
	int getX(); //returns xpos;
	int getY(); //returns ypos;
    private:
        int lock; //represents the door being locked
        int open; //represents the door being open
	int keyhole; //represents the type of key that needs to be used
	int xpos, ypos; //represents the location
};

#endif
