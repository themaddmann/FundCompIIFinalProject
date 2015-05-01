/*
 * Final Project
 * Steven Mike & Brian Mann
 * Implementation of Player Class
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <algorithm>
#include <iterator>
#include <string>
#include <fstream>
#include <cmath>
#include "Player.h"
#include "Person.h"
#include "Level.h"
#include "Door.h"
#include "DoorKey.h"
using namespace std;

//constructor
Player::Player() : Person(){
        xpos=20;
        ypos=20;
        health=3;
        speed=5;

	for(int i=0;i<7;i++){
		keys[i]=0;
	}
}

//player handles events
void Player::handleEvent(SDL_Event& e){

	//If a key was pressed (not including held down keys)
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0){

		//update velocity
		switch (e.key.keysym.sym){
			//double speed if space is pushed
			case SDLK_SPACE: 
				speed *= 2;
				break;
			case SDLK_DOWN: 
				yVel += 1;
				break;
			case SDLK_UP: 
				yVel -= 1;
				break;
			case SDLK_RIGHT: 
				xVel += 1;
				break;
			case SDLK_LEFT: 
				xVel -= 1;
				break;
		}
	}

	//if a key is released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0){
	
		//update velocity
		switch(e.key.keysym.sym){
			//halve speed if space is released
			case SDLK_SPACE: 
				speed /= 2;
				break;
			case SDLK_DOWN: 
				yVel -= 1;
				break;
			case SDLK_UP: 
				yVel += 1;
				break;
			case SDLK_RIGHT: 
				xVel -= 1;
				break;
			case SDLK_LEFT: 
				xVel += 1;
				break;
		}
	}
}

//moves the player
void Player::move(Level myLVL){

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

//player loses health if hit
//default damage is one
void Player::hit(int dmg){

	health -= dmg;
}

//ends the game by exiting the main loop
bool Player::gameOver(){

	if (health <= 0){

		//reset keys	
		for(int i=0;i<7;i++){
			keys[i]=0;
		}

		return true;
	}
	else return false;
}	

//getter and setter functions
//double Player::getX(){

//        return xpos;
//}

//double Player::getY(){

//        return ypos;
//}

int Player::getHealth(){

        return health;
}

void Player::setX(double newX){

        xpos = newX;
}

void Player::setY(double newY){

        ypos = newY;
}

void Player::setHealth(int newHealth){

        health = newHealth;
}

//sets the speed
void Player::setSpeed(double s){
	
	speed = s;
}

//returns keys
int* Player::getKeys(){

	return keys;
}

//adds a key
void Player::addKey(int newKey){

	keys[newKey]++;
}
