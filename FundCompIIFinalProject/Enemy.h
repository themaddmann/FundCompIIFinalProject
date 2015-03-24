// Base class for enemies
// Brain Mann
// 3/17/15
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
        virtual void setattack();
        virtual void setrange();
        virtual void setspeed();
        virtual void setsight();
        virtual int attack(int) == 0;
        virtual void move();
        virtual void pursue(double);
        virtual void sound(double);
    protected:
        int attackdamage;
        double attackrange;
        int movementspeed;
        double visionrange;
};

#endif
