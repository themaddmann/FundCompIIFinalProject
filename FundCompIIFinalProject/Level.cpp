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
//#include "Enemy.h"
using namespace std;

//constructor
Level::Level(){
	lvl = 1; //start at level 1
	rowMax = 2; //rows for level 1	
	colMax = 1; //columns for level 1
	//walls is dealt with in a separate function	
	
}

//set current level
void Level::setlvl(int l){
	
	lvl = l;
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
void Level::nextLVL(){
	
	lvl++;
	
	//reset allKeys
	allKeys.clear();

	//generate allKeys
	vector<DoorKey> currentKeys;
	vector< vector<DoorKey> > mapKeys; //gives in a given map col
	vector< vector< vector<DoorKey> > > mapRowKeys; //for a map row
	
	//lvl 1, map 00
	currentKeys.push_back(DoorKey(3,56,44));
	mapKeys.push_back(currentKeys);

	currentKeys.clear();

	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	//lvl 1 map 10
	currentKeys.push_back(DoorKey(5,276,555-480));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	allKeys.push_back(mapRowKeys);
	mapRowKeys.clear();

	//lvl 2 map 00
	currentKeys.push_back(DoorKey(4,20,20));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 2 map 01
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	//lvl 2 map 10
	currentKeys.push_back(DoorKey(6,265,877-480));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 2 map 11
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	allKeys.push_back(mapRowKeys);
	mapRowKeys.clear();

	//lvl 3 map 00
	currentKeys.push_back(DoorKey(7,25,25));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 3 map 01
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	//lvl 3 map 02
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	//lvl 3 map 10
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 3 map 11
	currentKeys.push_back(DoorKey(1,575,435));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	//lvl 3 map 12
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	//lvl 3 map 21
	currentKeys.push_back(DoorKey(2,25,435));
	mapKeys.push_back(currentKeys);
	currentKeys.clear();

	//lvl 3 map 21
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	//lvl 3 map 22
	mapKeys.push_back(currentKeys);
	currentKeys.clear();
	
	mapRowKeys.push_back(mapKeys);
	mapKeys.clear();

	allKeys.push_back(mapRowKeys);
	mapRowKeys.clear();

	//reset allDoors;
	allDoors.clear();

	//generate allDoors
	vector<Door> currentDoors;
	vector< vector<Door> > mapDoors; //gives in a given map col
	vector< vector< vector<Door> > > mapRowDoors; //for a map row
	
	//lvl 1, map 00
	currentDoors.push_back(Door(1,3,560,20));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	mapRowDoors.push_back(mapDoors);
	mapDoors.clear();

	//lvl 1 map 10
	currentDoors.push_back(Door(0,0,500,420));
	currentDoors.push_back(Door(1,5,300,420));
	currentDoors.push_back(Door(0,0,390,220));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	mapRowDoors.push_back(mapDoors);
	mapDoors.clear();

	allDoors.push_back(mapRowDoors);
	mapRowDoors.clear();

	//lvl 2, map 00
	currentDoors.push_back(Door(0,0,332,370));
	currentDoors.push_back(Door(1,6,576,65));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	//lvl 2, map 01
	currentDoors.push_back(Door(1,4,620,20));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	mapRowDoors.push_back(mapDoors);
	mapDoors.clear();

	//lvl 2, map 10
	currentDoors.push_back(Door(0,0,240,804-480));
	currentDoors.push_back(Door(0,0,240,743-480));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();
	
	//lvl 2, map 11
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	mapRowDoors.push_back(mapDoors);
	mapDoors.clear();

	allDoors.push_back(mapRowDoors);
	mapRowDoors.clear();	

	//lvl 3 map 00
	currentDoors.push_back(Door(1,1,220,20));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,220,360));
	currentDoors.push_back(Door(0,0,400,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	//lvl 3 map 01
	currentDoors.push_back(Door(0,0,220,20));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,220,360));
	currentDoors.push_back(Door(0,0,400,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();
	
	//lvl 3 map 02
	currentDoors.push_back(Door(0,0,220,20));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,220,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();
	
	mapRowDoors.push_back(mapDoors);
	mapDoors.clear();

	//lvl 3 map 10
	currentDoors.push_back(Door(0,0,220,20));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,400,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	//lvl 3 map 11
	currentDoors.push_back(Door(1,2,400,360));
	currentDoors.push_back(Door(0,0,220,20));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,220,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();
	
	//lvl 3 map 12
	currentDoors.push_back(Door(0,0,220,360));
	currentDoors.push_back(Door(0,0,220,20));
	currentDoors.push_back(Door(0,0,400,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();
	
	mapRowDoors.push_back(mapDoors);
	mapDoors.clear();

	//lvl 3 map 20
	currentDoors.push_back(Door(0,0,220,360));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,400,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();

	//lvl 3 map 21
	currentDoors.push_back(Door(0,0,220,20));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,220,360));
	currentDoors.push_back(Door(0,0,400,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();
	
	//lvl 3 map 22
	currentDoors.push_back(Door(1,7,620,230));
	currentDoors.push_back(Door(0,0,220,20));
	currentDoors.push_back(Door(0,0,400,20));
	currentDoors.push_back(Door(0,0,220,360));
	currentDoors.push_back(Door(0,0,400,360));
	mapDoors.push_back(currentDoors);
	currentDoors.clear();
	
	mapRowDoors.push_back(mapDoors);
	mapDoors.clear();

	allDoors.push_back(mapRowDoors);
	mapRowDoors.clear();

	switch(lvl){

		//specifications for level 1	
		case 1:
			rowMax=2;
			colMax=1;
			break;

		//specifications for level 2	
		case 2:
			rowMax = 2;
			colMax = 2;
			break;

		//specifications for level 3	
		case 3:
			rowMax=3;
			colMax=3;
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
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			//add top block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//repeat for left block
			block.push_back(0);
			block.push_back(19);
			block.push_back(0);
			block.push_back(479);
			//add left block to walls
			walls.push_back(block);
			//clear block
			block.clear();
			
			//repeat for right block
			block.push_back(620);
			block.push_back(639);
			block.push_back(0);
			block.push_back(479);
			//add right block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//repeat for all blocks of walls
			block.push_back(250);
			block.push_back(269);
			block.push_back(0);
			block.push_back(199);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(320);
			block.push_back(339);
			block.push_back(0);
			block.push_back(199);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(500);
			block.push_back(519);
			block.push_back(0);
			block.push_back(219);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(560);
			block.push_back(579);
			block.push_back(60);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(190);
			block.push_back(209);
			block.push_back(250);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(500);
			block.push_back(519);
			block.push_back(280);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(64);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(110);
			block.push_back(519);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();
		}

		else if(map[0]==1 && map[1]==0){
			
			block.push_back(0);
			block.push_back(64);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(110);
			block.push_back(519);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			//repeat for left block
			block.push_back(0);
			block.push_back(19);
			block.push_back(0);
			block.push_back(479);
			//add left block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			//repeat for right block
			block.push_back(620);
			block.push_back(639);
			block.push_back(0);
			block.push_back(479);
			//add right block to walls
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(190);
			block.push_back(209);
			block.push_back(20);
			block.push_back(759-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(210);
			block.push_back(409);
			block.push_back(200);
			block.push_back(219);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(390);
			block.push_back(409);
			block.push_back(260);
			block.push_back(879-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(259);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(300);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(240);
			block.push_back(259);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(240);
			block.push_back(519);
			block.push_back(400);
			block.push_back(419);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(500);
			block.push_back(519);
			block.push_back(0);
			block.push_back(419);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(560);
			block.push_back(579);
			block.push_back(0);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

		}

		break;

		case 2:

		if (map[0] == 0 && map[1] == 0){
			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(19);
			block.push_back(0);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(20);
			block.push_back(199);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(179);
			block.push_back(199);
			block.push_back(329);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(240);
			block.push_back(259);
			block.push_back(328);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(260);
			block.push_back(531);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(512);
			block.push_back(531);
			block.push_back(410);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(332);
			block.push_back(531);
			block.push_back(410);
			block.push_back(429);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(332);
			block.push_back(531);
			block.push_back(350);
			block.push_back(369);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(512);
			block.push_back(531);
			block.push_back(0);
			block.push_back(369);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(576);
			block.push_back(595);
			block.push_back(0);
			block.push_back(64);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(576);
			block.push_back(595);
			block.push_back(100);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(596);
			block.push_back(639);
			block.push_back(45);
			block.push_back(64);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(596);
			block.push_back(639);
			block.push_back(100);
			block.push_back(179);
			walls.push_back(block);
			//clear block
			block.clear();


			}

		if (map[0] == 0 && map[1] == 1){
			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(620);
			block.push_back(639);
			block.push_back(60);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(976-640);
			block.push_back(45);
			block.push_back(64);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(-60);
			block.push_back(976-640);
			block.push_back(100);
			block.push_back(119);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(957-640);
			block.push_back(976-640);
			block.push_back(0);
			block.push_back(64);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(957-640);
			block.push_back(976-640);
			block.push_back(100);
			block.push_back(299);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(977-640);
			block.push_back(639);
			block.push_back(280);
			block.push_back(299);
			walls.push_back(block);
			//clear block
			block.clear();

			}

		if (map[0] == 1 && map[1] == 0){
			block.push_back(620);
			block.push_back(639);
			block.push_back(694-480);
			block.push_back(393);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(620);
			block.push_back(639);
			block.push_back(0);
			block.push_back(649-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(679);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(20);
			block.push_back(0);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(199);
			block.push_back(880-480);
			block.push_back(899-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(180);
			block.push_back(199);
			block.push_back(0);
			block.push_back(899-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(199);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(180);
			block.push_back(259);
			block.push_back(784-480);
			block.push_back(804-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(240);
			block.push_back(259);
			block.push_back(0);
			block.push_back(744-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(240);
			block.push_back(531);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(576);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(240);
			block.push_back(639);
			block.push_back(854-480);
			block.push_back(873-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(240);
			block.push_back(259);
			block.push_back(844-480);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			}

		if (map[0] == 1 && map[1] == 1){
			block.push_back(620);
			block.push_back(639);
			block.push_back(0);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(-60);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(19);
			block.push_back(0);
			block.push_back(649-480);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(19);
			block.push_back(694-480);
			block.push_back(399);
			walls.push_back(block);
			//clear block
			block.clear();


		}
		break;
		case 3:
		if (map[0] == 0 && map[1] == 0){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

		

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();
		
			block.push_back(0);
			block.push_back(19);
			block.push_back(0);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();
		}

		if (map[0] == 0 && map[1] == 1){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

		
		}

		if (map[0] == 0 && map[1] == 2){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(0);
			block.push_back(1855-1280);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
		
			block.push_back(0);
			block.push_back(1855-1280);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(620);
			block.push_back(639);
			block.push_back(0);
			block.push_back(539);
			walls.push_back(block);
			//clear block
			block.clear();
		}

		if (map[0] == 1 && map[1] == 2){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(1855-1280);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
		
			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(1855-1280);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(620);
			block.push_back(639);
			block.push_back(-60);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();
		}

		if (map[0] == 1 && map[1] == 1){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

		
		}

		if (map[0] == 1 && map[1] == 0){
			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(64);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(64);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(19);
			block.push_back(0);
			block.push_back(539);
			walls.push_back(block);
			//clear block
			block.clear();
		
		}

		if (map[0] == 2 && map[1] == 0){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left;
			block.push_back(64);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(64);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(19);
			block.push_back(-60);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();
		
		}

		if (map[0] == 2 && map[1] == 1){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

		
		}

		if (map[0] == 2 && map[1] == 2){
			//add bottom-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add bottom-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(340);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-right edge wall
			block.push_back(620);
			block.push_back(699);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//add top-left edge wall
			block.push_back(-60);
			block.push_back(19);
			block.push_back(0);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			//top left
			block.push_back(220);
			block.push_back(239);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(239);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();
			//bottom left
			block.push_back(0);
			block.push_back(239);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(220);
			block.push_back(239);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			//Bottom Right
			block.push_back(400);
			block.push_back(639);
			block.push_back(340);
			block.push_back(359);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(400);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(639);
			block.push_back(120);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(400);
			block.push_back(419);
			block.push_back(60);
			block.push_back(139);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(460);
			block.push_back(479);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(0);
			block.push_back(639);
			block.push_back(0);
			block.push_back(19);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(620);
			block.push_back(639);
			block.push_back(0);
			block.push_back(230);
			walls.push_back(block);
			//clear block
			block.clear();

			block.push_back(620);
			block.push_back(639);
			block.push_back(270);
			block.push_back(479);
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

	doors=allDoors[lvl-1][map[0]][map[1]];

}


//interacts with the door
void Level::doorInteract(int i,int keys[7],int map[]){

	doors[i].interact(keys);

	allDoors[lvl-1][map[0]][map[1]] = doors;
}

//updates the keys based on level and map
void Level::updateKeys(int map[]){

	//determines the location of keys based on level and the specific map	

	//clear keys
	keys.clear();

	keys=allKeys[lvl-1][map[0]][map[1]];
}	

//picks up a key and updates accordingly
void Level::pickKey(int k, int map[]){

	keys[k].setPicked(1);
	
	allKeys[lvl-1][map[0]][map[1]] = keys;
}

//updates enemies based on level and map
void Level::updateEnemies(int map[]){

	//determines the location of enemies based on level and the specific map	
	//clear enemies
	enemies.clear();
	
	switch (lvl){
	
		//add in the enemies	
		case 2:
		if (map[0]==0 && map[1]==0){

			vector<int> enemy1;
			enemy1.push_back(190); // x position
			enemy1.push_back(130); // y position
			enemies.push_back(enemy1);	

		}
		break;
		case 3:
		if (map[0]==0 && map[1]==0){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
			vector<int> enemy2;
			enemy2.push_back(50); // x position
			enemy2.push_back(50); // y position
			enemies.push_back(enemy2);	
		}
		if (map[0]==0 && map[1]==1){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		if (map[0]==0 && map[1]==2){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		if (map[0]==1 && map[1]==0){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		if (map[0]==1 && map[1]==1){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		if (map[0]==1 && map[1]==2){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		if (map[0]==2 && map[1]==0){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		if (map[0]==2 && map[1]==1){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		if (map[0]==2 && map[1]==2){
			vector<int> enemy1;
			enemy1.push_back(305); // x position
			enemy1.push_back(223); // y position
			enemies.push_back(enemy1);	
		}
		break;
	}
}

//returns enemies
vector< vector<int> > Level::getEnemies(){

	return enemies;
}


