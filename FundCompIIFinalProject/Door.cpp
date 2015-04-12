// Driver class for Door.h
// Brian Mann and Steven Mike
// 4/11/15
// Door.cpp

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
#include "Door.h"
using namespace std;

Door::Door(int opened, int locked){
    open = opened;
    locked = lock;
}

int Door::isOpen(){
    if(open==1){
        return 1;
    }else{
        return 0;
    }
}

int Door::isLocked(){
    if(lock==1){
        return 1;
    }else{
        return 0;
    }
}

void Door::setOpen(){
    open=1;
}

void Door::setClosed(){
    open=0;
}
