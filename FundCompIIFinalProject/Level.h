/*
 * Level Class for Final Project
 * Steven Mike & Brian Mann
 * Used to store information about the different levels and pass it to the program
 */

#ifndef LEVEL_H
#define LEVEL_H

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Door.h"
#include "DoorKey.h"
//#include "Enemy.h"
//#include "Player.h"
using namespace std;

class Level{

	public:
		Level(); //constructor
		int getlvl(); //returns the current level
		int getRows(); //returns number of rows on the map
		int getCols(); //returns number of columns on the map
		void nextLVL(); //increases the level
		void updateWalls(int[]); //updates the walls based on level and map
		void updateDoors(int[]); //updates the doors based on level and map
		void updateKeys(int[]); //updates the keys based on level and map
		vector< vector<int> > getWalls(); //returns the 2D-vector walls
		vector<Door> getDoors(); //returns the doors
		vector<DoorKey> getKeys(); //returns the keys
		void doorInteract(int,int[7],int[]); //interacts with the door
		void pickKey(int,int[2]); //picks up a key
		vector< vector<int> > getEnemies(); //returns enemies vector
		void updateEnemies(int[]); //updates enemies based on level and map
		void setlvl(int); //sets lvl
	private:
		int lvl; //the current level
		int rowMax; //the max number of rows on the current map grid
		int colMax; //the max number of columns on the current map grid
		vector< vector<int> > walls; //represents the location of the walls
		vector<Door> doors; //represents the location of the doors
		vector<DoorKey> keys; //represents the location of the keys for a given map
		vector< vector< vector< vector<DoorKey> > > > allKeys; //represents all the keys
		vector< vector< vector< vector<Door> > > > allDoors; //represents all the doors

		vector< vector<int> > enemies; //holds position information for enemies

};

#endif
