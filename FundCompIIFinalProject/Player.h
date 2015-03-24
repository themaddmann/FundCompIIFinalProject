/*
 * Player Class for Final Project
 * Steven Mike & Brian Mann
 * Very basic for the time being. Will increase in complexity as more of the SD$
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;

class Player {

        public:
                Player();
                void move();
                void run();
                //add function to change angle once more is known about key fun$
                //getter and setter methods
                double getX();
                double getY();
                int getHealth();
                void setX(double);
                void setY(double);
                void setHealth(int);

        private:
                double xpos;
                double ypos;
                int health;
                double speed;
                double angle;//direction
                int running; //boolean
};

#endif
