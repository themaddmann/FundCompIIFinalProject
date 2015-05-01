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
#include "Player.h"
#include "Level.h"
#include <cmath>
using namespace std;

//constructor
Enemy::Enemy(int x, int y, int d, int r, int s, int v, bool p) : Person(){
	dmg = d;
	range = r;
	speed = s;
	vision = v;
	pursuit = p;
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

//enemy attacks the player, returns true if attack connects
Player Enemy::attack(Player p){

	p.hit(dmg);
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


//checks the player's position relative to the enemy's and updates enemy 
void Enemy::update(Level myLVL, Player *p){


	//set velocities to 0
	xVel = 0;
	yVel = 0;
	//get Player location
	double pX = (*p).getX();
	double pY = (*p).getY();

	//see if the player is within vision range
	if (pX <= (xpos) + vision && pX >= (xpos) - vision){
		if (pY <= (ypos) + vision && pY >= (ypos) - vision){

			pursuit = true;
		}
	}

	else pursuit = false;

	if (pursuit){

		//see if player is within attack range
		if((pX <= (xpos) + range && pX >= (xpos) - range)&&(pY <= (ypos) + range && pY >= (ypos) - range)){

				*p = attack(*p);
		}

		else{
			//have enemy chase player
			updateVelocity(myLVL, pX,pY);
//			if (pX > xpos) xVel = 1;
//			else if (pX < xpos) xVel = -1;
//			if (pY > ypos) yVel = 1;
//			else if (pY < ypos) yVel = -1;
		}

	}
}

//finds the distance between two points
double Enemy::distance(double x1, double y1, double x2, double y2){

	double x = pow(x2-x1,2.0);
	double y = pow(y2-y1,2.0);
	double dist = sqrt(x+y);
	return dist;
}

//updates velocity to get shortest path to player considering placement of walls
void Enemy::updateVelocity(Level myLVL, double pX, double pY){


	//Don't want the enemy to continually run into walls, so we need to check all possible velocities to see which combo will bring the enemy closest to the player
	double oDist = distance(xpos,ypos,pX,pY);
	double dist = oDist;
	double newDist;
	int x = 0;
	int y = 0;
	//store original position
	double ox = xpos;
	double oy = ypos;
	
	
	//set new potential velocity
	xVel = 1;
	yVel = 1;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = 1;
		y = 1;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = 1;
	yVel = 0;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = 1;
		y = 0;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = 1;
	yVel = -1;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = 1;
		y = -1;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = 0;
	yVel = 1;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = 0;
		y = 1;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = 0;
	yVel = 0;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = 0;
		y = 0;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = 0;
	yVel = -1;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = 0;
		y = -1;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = -1;
	yVel = 1;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = -1;
		y = 1;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = -1;
	yVel = 0;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = -1;
		y = 0;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	//set new potential velocity
	xVel = -1;
	yVel = -1;
	//move enemy
	move(myLVL);
	//find new distance
	newDist = distance(xpos,ypos,pX,pY);
	//see if new distance is shorter
	if (newDist < dist){
		dist = newDist;
		x = -1;
		y = -1;
	}
	//move enemy back to original spot
	xpos = ox;
	ypos = oy;

	xVel = x;
	yVel = y;
}
