/*
 * Final Project
 * Steven Mike $ Brian Mann
 * Implementation of the Level class
 */

#include <iostream>
#include <SDL2/SDL.h>
#include "Level.h"
#include "Door.h"
#include "DoorKey.h"
#include "Enemy.h"
using namespace std;

//constructor
Level::Level(){
	lvl = 1; //start at level 1
	rowMax = 1; //rows for level 1	
	colMax = 2; //columns for level 1
	//walls is dealt with in a separate function	
	

	//generate allKeys
	vector<DoorKey> currentKeys;
	vector< vector<DoorKey> > mapKeys; //gives in a given map col
	vector< vector< vector<DoorKey> > > mapRowKeys; //for a map row
	
	//lvl 1, map 00
	currentKeys.push_back(DoorKey(7,200,200));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 1 map 01
	currentKeys.push_back(DoorKey(3,200,200));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 1 map 02
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	//lvl 1 map 10
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 1 map 11
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 1 map 12
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	allKeys.push_back(mapRowKeys);
	mapRowKeys.clear();
}

//returns the current level
int Level::getlvl(){
	
	return lvl;
}

//returns the maximum rows for the map
int Level::getRows(){

	return rowMax;
}

//returns the maximum columns for the map
int Level::getCols(){

	return colMax;
}

//used when the next level is reached 
//changes the appropriate variables based on each levels specifications
void Level::operator++(){
	
	lvl++;

	switch(lvl){

		//specifications for level 2	
		case 2:
			//
			break;

		//specifications for level 3	
		case 3:
			//
			break;

		//specifications for level 4	
		case 4:
			//
			break;

		//specifications for level 5	
		case 5:
			//
			break;
	}
}


//returns the walls 2D-vector
vector< vector<int> > Level::getWalls(){

	return walls;
}

//updates the walls based on level and map
void Level::updateWalls(int map[]){


	//determines the location of walls based on level and the specific map	
	//the first dimension holds the block of walls
	//the second dimension holds the four corners x1, x2, y1, y2 of each block

	//clear walls
	walls.clear();
	
	//create vector of ints
	vector<int> block;
	switch (lvl){
		
		case 1:
		if (map[0]==0 && map[1]==0){

			//fill in top block
			block.push_back(0);
			block.push_back(640);
			block.push_back(0);
			block.push_back(20);
			//add top block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//repeat for left block
			block.push_back(0);
			block.push_back(20);
			block.push_back(0);
			block.push_back(480);
			//add left block to walls
			walls.push_back(block);
			//clear block
			block.clear();
			
			//repeat for right block
			block.push_back(600);
			block.push_back(640);
			block.push_back(0);
			block.push_back(400);
			//add right block to walls
			walls.push_back(block);
			//clear block
			block.clear();
		}

		else if(map[0]==1 && map[1]==0){
			
			//fill in bottom block
			block.push_back(0);
			block.push_back(640);
			block.push_back(460);
			block.push_back(480);
			//add bottom block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//repeat for left block
			block.push_back(0);
			block.push_back(20);
			block.push_back(0);
			block.push_back(480);
			//add left block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//repeat for right block
			block.push_back(600);
			block.push_back(640);
			block.push_back(80);
			block.push_back(480);
			//add right block to walls
			walls.push_back(block);
			//clear block
			block.clear();

		}
		else if(map[0]==0 && map[1]==1){
			//fill in top block
			block.push_back(0);
			block.push_back(640);
			block.push_back(0);
			block.push_back(20);
			//add top block to walls
			walls.push_back(block);
			//clear block
			block.clear();	

		}
		else if(map[0]==1 && map[1]==1){
			//fill in bottom block
			block.push_back(0);
			block.push_back(640);
			block.push_back(460);
			block.push_back(480);
			//add bottom block to walls
			walls.push_back(block);
			//clear block
			block.clear();

		}
		else if(map[0]==0 && map[1]==2){
			//fill in top block
			block.push_back(0);
			block.push_back(640);
			block.push_back(0);
			block.push_back(20);
			//add top block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//fill in right block
			block.push_back(620);
			block.push_back(640);
			block.push_back(0);
			block.push_back(480);
			//add right block to walls
			walls.push_back(block);
			//clear block
			block.clear();
		}
		else if(map[0]==1 && map[1]==2){
			//fill in bottom block
			block.push_back(0);
			block.push_back(640);
			block.push_back(460);
			block.push_back(480);
			//add bottom block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//fill in right block
			block.push_back(620);
			block.push_back(640);
			block.push_back(0);
			block.push_back(480);
			//add right block to walls
			walls.push_back(block);
			//clear block
			block.clear();
		
		}
				

		break;
	}
}



//return the Doors
vector<Door> Level::getDoors(){

	return doors;
}

//return the Keys
vector<DoorKey> Level::getKeys(){

	return keys;
}

//updates the doors based on level and map
void Level::updateDoors(int map[]){

	//determines the location of doors based on level and the specific map	

	//clear doors
	doors.clear();
	
	switch (lvl){
		
		case 1:
		if (map[0]==0 && map[1]==0){

			Door door1(0,0,50,50);
			doors.push_back(door1);	
			Door door2(1,7,100,100);
			doors.push_back(door2);	

		}
		else if(map[0]==1 && map[1]==0){
			
			Door door1(1,1,50,50);
			doors.push_back(door1);	

		}
		else if(map[0]==0 && map[1]==1){

			Door door1(1,2,50,50);
			Door door2(1,3,100,100);
			doors.push_back(door1);	
			doors.push_back(door2);	
		}
		else if(map[0]==1 && map[1]==1){

			Door door1(1,4,50,50);
			Door door2(1,5,100,100);
			doors.push_back(door1);	
			doors.push_back(door2);	
		}
		else if(map[0]==0 && map[1]==2){

			Door door1(1,6,50,50);
			doors.push_back(door1);	
		}
		else if(map[0]==1 && map[1]==2){
		
			Door door1(1,7,50,50);
			doors.push_back(door1);	
		}
		break;
	}
}


//interacts with the door
void Level::doorInteract(int i,int keys[7]){

	doors[i].interact(keys);
}

//updates the keys based on level and map
void Level::updateKeys(int map[]){

	//determines the location of keys based on level and the specific map	

	//clear doors
	keys.clear();

	keys=allKeys[lvl-1][map[0]][map[1]];
}	

//picks up a key and updates accordingly
void Level::pickKey(int k, int map[]){

	keys[k].setPicked(1);
	
	allKeys[lvl-1][map[0]][map[1]] = keys;
}
/*
//updates enemies based on level and map
void Level::updateDoors(int map[]){

	//determines the location of enemies based on level and the specific map	
	//clear enemies
	enemies.clear();
	
	switch (lvl){
		
		case 1:
		if (map[0]==0 && map[1]==0){

			Enemy enemy1(300,300);
			enemies.push_back(enemy1);	

		}
		else if(map[0]==1 && map[1]==0){
			

		}
		else if(map[0]==0 && map[1]==1){

		}
		else if(map[0]==1 && map[1]==1){

		}
		else if(map[0]==0 && map[1]==2){

		}
		else if(map[0]==1 && map[1]==2){
		
		}
		break;
	}
}
*/
//returns enemies
//vector<Enemy> Level::getEnemies(){

//	return enemies;
//}
