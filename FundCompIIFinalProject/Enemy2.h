// Class for enemies
// Brain Mann
// 4/8/15
// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Enemy{
    public:
        Enemy();
        int attack();
        int pursue(int,int,int);
        void sound();
        int getenemyX();
        int getenemyY();
        void setenemyX(int);
        void setenemyY(int);
        char openDoor();
    private:
        int xposition;
        int yposition;
        int attackdamage;
        int attackrange;
        int movementspeed;
        int visionrange;
};

#endif
