/*
 * Player Class for Final Project
 * Steven Mike & Brian Mann
 * Very basic for the time being. Will increase in complexity as more of the SD$
*/

#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <vector>
#include "Person.h"
#include "Level.h"
using namespace std;

class Player : public Person {

        public:
                Player();
                void move(Level); //moves character based on velocities
		void handleEvent(SDL_Event&); //player handles events
		void hit(int = 1); //player loses health if hit
		bool gameOver(); //If health hits 0, game is over
                //getter and setter methods
        //        double getX();
      //          double getY();
                int getHealth();
                void setX(double);
                void setY(double);
		void setSpeed(double);
                void setHealth(int);
		int* getKeys(); //returns keys
		void addKey(int); //adds a key
        private:
                int health;
                double speed;
		int keys[7]; //represents picked up keys
};

#endif
