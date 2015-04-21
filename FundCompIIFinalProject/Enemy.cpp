/*
 * Final Project
 * Steven Mike & Brian Mann
 * Implementation for abstract Enemy class
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <vector>
#include "Enemy.h"
#include "Person.h"
using namespace std;

//constructor
Enemy::Enemy(int x, int y) : Person(){
	dmg = 1;
	range = 3;
	speed = 5;
	vision=50;
	pursuit = false;
	xpos = x;
	ypos = y;
}

//returns dmg
int Enemy::getDMG(){

	return dmg;
}

//returns range
double Enemy::getRange(){

	return range;
}

//returns speed
int Enemy::getSpeed(){

	return speed;
}

//returns vision
double Enemy::getVision(){

	return vision;
}

//returns pursuit
bool Enemy::inPursuit(){

	return pursuit;
}
/*
//enemy attacks the player, returns true if attack connects
Player Enemy::attack(Player p){

	//check if player is within attack range
	if (p.getX() <= xpos + range && p.getX() >= xpos - range)
		if (p.getY() <= ypos + range && p.getY() > ypos - range){
			p.hit(dmg);
		}
	return p;
}

//moves enemy based on walls and velocity
void Enemy::move(Level myLVL){

	//get information for the walls
	vector< vector<int> > walls = myLVL.getWalls();

	//get information for the doors
	vector<Door> doors = myLVL.getDoors();

	//create an iterator for walls
	//no iterator for *iter is needed since there's always 4 elements
	vector< vector<int> >::iterator iter;
	
	//iterator for doors
	vector<Door>::iterator diter;

	//make a closed door function as a wall
	vector<int> block;
	for(diter=doors.begin();diter!=doors.end();++diter){
		if(! (*diter).isOpen()){	

			block.push_back((*diter).getX());
			block.push_back((*diter).getX()+20);
			block.push_back((*diter).getY());
			block.push_back((*diter).getY()+40);
			walls.push_back(block);
			block.clear();
		}
	}
	
	//update position based on speed and velocity
	
	//update x
	xpos += speed * xVel;

	//make sure player won't walk inside a wall
	//push player to edge of wall if so
	for(iter=walls.begin();iter != walls.end(); ++iter){

		//check if character is within the Xs at all
		if ((xpos>(*iter)[0] && xpos<(*iter)[1]) || (xpos+30>(*iter)[0] && xpos+30<(*iter)[1]) || (xpos+15>(*iter)[0] && xpos+15<(*iter)[1])){
			//check if character is within the Ys at all
			if ((ypos>(*iter)[2] && ypos<(*iter)[3]) || (ypos+35>(*iter)[2] && ypos+35<(*iter)[3]) || (ypos+17>(*iter)[2] && ypos+17<(*iter)[3])){

				//push the player to the appropriate edge
				if ((xpos>(*iter)[0]&&xpos<(*iter)[1]) && !(xpos+30>(*iter)[0]&&xpos+30<(*iter)[1]))
					xpos += (*iter)[1]-xpos;
				else if ((xpos+30>(*iter)[0]&&xpos+30<(*iter)[1]) && !(xpos>(*iter)[0]&&xpos<(*iter)[1]))
					xpos += (*iter)[0]-(xpos+30);
			}
		}
	}

	ypos += speed * yVel;
	
	//MUST DO THIS AGAIN TO MAKE SURE STILL NO INTERSECTION FROM Ys
	//make sure player won't walk inside a wall
	//push player to edge of wall if so
	for(iter=walls.begin();iter != walls.end(); ++iter){

		//check if character is within the Xs at all
		if ((xpos>(*iter)[0] && xpos<(*iter)[1]) || (xpos+30>(*iter)[0] && xpos+30<(*iter)[1]) || (xpos+15>(*iter)[0] && xpos+15<(*iter)[1])){
			//check if character is within the Ys at all
			if ((ypos>(*iter)[2] && ypos<(*iter)[3]) || (ypos+35>(*iter)[2] && ypos+35<(*iter)[3]) || (ypos+17>(*iter)[2] && ypos+17<(*iter)[3])){
				if ((ypos>(*iter)[2]&&ypos<(*iter)[3]) && !(ypos+35>(*iter)[2] && ypos+35<(*iter)[3]))
					ypos += (*iter)[3]-ypos;
				else if ((ypos+35>(*iter)[2]&&ypos+35<(*iter)[3]) && !(ypos>(*iter)[2] && ypos<(*iter)[3]))
					ypos += (*iter)[2]-(ypos+35);
			}	
		}
	}
}
*/
