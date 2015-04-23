// Base class for enemies
// Brian Mann
// 3/17/15
// Enemy.h

#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <SDL2/SDL.h>
#include <string>
#include <fstream>
#include <vector>
#include "Person.h"
#include "Level.h"
#include "Player.h"
using namespace std;

class Enemy : public Person {

    public:
        Enemy(int,int); //constructor
	int getDMG(); //returns dmg
	double getRange(); //returns range
	int getSpeed(); //returns speed
	double getVision(); //returns vision
	bool inPursuit(); //returns pursuit
//	Player attack(Player); //enemy attacks the player, returns true if attack connects
//        virtual void pursue()=0; //enemy pursues
//        virtual void sound()=0; //sound
//	void move(Level); //moves enemy based on velocities and walls
    private:
        int dmg; //represents the damage the enemy does in a hit
        double range; //represents the range of the enemy's attack
        int speed; //represents the movement speed
        double vision; //represents the vision range
	bool pursuit; //represents if the enemy is chasing the player or not
};

#endif
