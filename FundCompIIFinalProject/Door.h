// Class for doors
// Brian Mann and Steven Mike
// 4/11/15
// Door.h

#ifndef DOOR_H
#define DOOR_H

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Door{
    public:
        Door(int = 1,int = 0);
        int isOpen();
        int isLocked();
        void setOpen();
        void setClosed();
    private:
        int lock;
        int open;
};
