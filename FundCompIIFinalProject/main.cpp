/*
 * Final Project
 * Main driver program
 * Steven Mike & Brian Mann
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>
#include "SDLClasses.h"
#include "Player.h"
#include "Level.h"
#include "Person.h"
//#include "Enemy.h"
using namespace std;

Player updateBackground(Player,int[],Level);


//DEBUGGER
int DBCount = 0;
int main(int argc, char* args[]){


	if(!init()) printf("Failed to initialize!\n");
	else{

		//load media
		if(!loadMedia()){
			printf("Failed to load media!\n");
		}

		else {
			//create the player
		        Player p = Player();

			//create array to determine which map the player is on
			//thinking of each map as a grid, map[0] is the row, and map[1] is the column
			int map[2] = {0,0};
			int oldMap[2]={0,0}; //holds the previous map

			//create the Level object
			Level myLVL;

			//create first set of walls doors and keys	

			//update walls
			myLVL.updateWalls(map);
					
			//update doors and keys
			myLVL.updateDoors(map); 
			myLVL.updateKeys(map);

			//update enemies
//			myLVL.updateEnemies(map);
			//Main loop flag
			bool over = false;
	
			//Event handler
			SDL_Event e;

			int type,doorX,doorY; //will hold information for a door
			int keyX,keyY; //holds information for a key	
			int enemyX,enemyY; //holds information for an enemy
			while (!over){
				
			
				//sets over to true if the character is dead
				over = p.gameOver();
	
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0){
					if (e.type == SDL_QUIT){
						over = true;
					}

					//pass events to the player
					p.handleEvent(e);
				}


				p.move(myLVL);	
				
				//update background if necessary
				p = updateBackground(p,map,myLVL);

				//update walls doors and keys if map has changed
				if (map[0] != oldMap[0] || map[1] != oldMap[1]){

					oldMap[0]=map[0];
					oldMap[1]=map[1];
					//update walls
					myLVL.updateWalls(map);
					
					//update doors and keys
					myLVL.updateDoors(map); 
					myLVL.updateKeys(map);

					//update enemies
//					myLVL.updateEnemies(map);
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
				SDL_RenderClear(gRenderer);
		
				//Render background
				gBackTexture.render(0,0,&gBackgroundClip);

				//Render Doors and keys
				//need to use incrementer because an iterator cuases the program to freeze for whatever reason
				
				//Render and interact with Doors
				for(int j=0;j<(myLVL.getDoors()).size();j++){
						
					type = 4*myLVL.getDoors()[j].getType();
					doorX =  myLVL.getDoors()[j].getX();
					doorY =  myLVL.getDoors()[j].getY();
					if(myLVL.getDoors()[j].isOpen())type+=3;
					gDoorTexture.render(doorX,doorY,&gDoorClips[type]);
					//check to see if door should be interacted with
					if(! myLVL.getDoors()[j].isOpen() && (p.getX()-doorX>=-30 && p.getX()-doorX<=20 && p.getY()-doorY>=-35 && p.getY()-doorY<=40)){
						myLVL.doorInteract(j,p.getKeys());
					}
				}

				//Render and interact with Keys
				for(int j=0;j<(myLVL.getKeys()).size();j++){
					if (!myLVL.getKeys()[j].pickedUp()){	
						type =  myLVL.getKeys()[j].getType()-1;
						keyX =  myLVL.getKeys()[j].getX();
						keyY =  myLVL.getKeys()[j].getY();
						gKeyTexture.render(keyX,keyY,&gKeyClips[type]);
						//check to see if key should be picked
						if((p.getX()-keyX>=-30 && p.getX()-keyX<=30 && p.getY()-keyY>=-35 && p.getY()-keyY<=15)){
							myLVL.pickKey(j,map);
							p.addKey(type);
						}
					}
				}

				//render Enemy
//				for(int j=0;j<(myLVL.getEnemies()).size();j++){
//					enemyX =  myLVL.getEnemies()[j].getX();
//					enemyY =  myLVL.getEnemies()[j].getY();
//					gEnemyTexture.render(enemyX,enemyY,&gEnemyClips[0]);
//				}
					
				//Render player
				gPlayerTexture.render(p.getX(),p.getY(),&gPlayerClips[0]);
				
				//make is so blackout moves with character. Need to center field of vision at character center
				gBlackoutTexture.render((-750+PLAYER_WIDTH/2)+p.getX(),(-750+PLAYER_HEIGHT/2)+p.getY());
				//Update screen
				SDL_RenderPresent(gRenderer);
			}
	
		}
	close();
	}
}




//updates the background based on the player's location 
//changes player location if they enter new map
Player updateBackground(Player p, int map[], Level myLVL){
	
	//Player walks off the right
	if(p.getX() >= SCREEN_WIDTH && map[1] < myLVL.getCols()){
		gBackgroundClip.x += SCREEN_WIDTH;
		p.setX(0);
		map[1]++;
	}			
	//Player walks off the bottom
	if(p.getY() >= SCREEN_HEIGHT && map[0] < myLVL.getRows()){
		gBackgroundClip.y += SCREEN_HEIGHT;
		p.setY(0);
		map[0]++;
	}			
	//Player walks off the left
	if(p.getX() <= -1*PLAYER_WIDTH && map[1]>0){
		gBackgroundClip.x -= SCREEN_WIDTH;
		p.setX(SCREEN_WIDTH-PLAYER_WIDTH);
		map[1]--;
	}			
	//Player walks off the top
	if(p.getY() <= -1* PLAYER_HEIGHT && map[0]>0){
		gBackgroundClip.y -= SCREEN_HEIGHT;
		p.setY(SCREEN_HEIGHT-PLAYER_HEIGHT);
		map[0]--;
	}

	return p;
}


