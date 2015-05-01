// Base class for enemies
// Steven Mike & Brian Mann
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
        Enemy(int,int,int=1,int=20,int=6,int=150,bool=false); //constructor
	int getDMG(); //returns dmg
	double getRange(); //returns range
	int getSpeed(); //returns speed
	double getVision(); //returns vision
	bool inPursuit(); //returns pursuit
	Player attack(Player); //enemy attacks the player, returns true if attack connects
	void update(Level, Player*);
	void move(Level); //moves enemy based on velocities and walls
	double distance(double,double,double,double); //finds the distance between two points
	void updateVelocity(Level,double,double); //updates the Enemy's velocity
    private:
        int dmg; //represents the damage the enemy does in a hit
        double range; //represents the range of the enemy's attack
        int speed; //represents the movement speed
        double vision; //represents the vision range
	bool pursuit; //represents if the enemy is chasing the player or not
};

#endif
