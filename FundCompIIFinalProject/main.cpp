/*
 * Final Project
 * Main driver program
 * Steven Mike & Brian Mann
 */

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <cmath>
#include "SDLClasses.h"
#include "Player.h"
#include "Level.h"
#include "Person.h"
#include "Enemy.h"
using namespace std;

Player updateBackground(Player,int[],Level);


int main(int argc, char* args[]){


	if(!init()) printf("Failed to initialize!\n");
	else{

		//load media
		if(!loadMedia()){
			printf("Failed to load media!\n");
		}

		else {

			int frame = 0;
			int type,doorX,doorY; //will hold information for a door
			int keyX,keyY; //holds information for a key	
			int enemyX,enemyY; //holds information for an enemy
			int sprite = 0; //holds info for which sprite to use

			//create the player
		        Player p = Player();

			//create a vector to hold the enemies
			vector<Enemy> enemies;
			vector<Enemy>::iterator eiter;

			//create array to determine which map the player is on
			//thinking of each map as a grid, map[0] is the row, and map[1] is the column
			int map[2] = {0,0};
			int oldMap[2]={0,0}; //holds the previous map

			//create the Level object
			Level myLVL;


			//Main loop flag
			bool over = false; //True if user exits
			bool dead = false; //True if player dies
	
			//Event handler
			SDL_Event e;
			//start the music
			//Mix_PlayChannel(-1,gDoorOpen,0);
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
			SDL_RenderClear(gRenderer);
		
			//Bring up Title Screen	
			gCoverTexture.render(0,0);
			gTitleTexture.render(0,0);

			//Update screen
			SDL_RenderPresent(gRenderer);

			//Start game once start is pushed
			bool start = false;
			int mX, mY; //holds mouse position
			while(!start && !over){
				while (SDL_PollEvent(&e) != 0){

					//check to see if user has quit
					if (e.type == SDL_QUIT) over = true;
					//check for button click
					if (e.type == SDL_MOUSEBUTTONDOWN){
						//make sure mouse is over start
						SDL_GetMouseState(&mX,&mY);
						if (mX <= 408 && mX >= 230 && mY <= 413 && mY >= 351){
							start = true;
						}
					}
				}
			}
			bool cont = true;
			while (cont && !over){
				cont = false;
				dead = false;
				//set the starting positions
				switch(myLVL.getlvl()){

					case 1:
						p.setX(275);
						p.setY(30);
						myLVL.setlvl(0);
						myLVL.nextLVL();
						map[0]=0;
						map[1]=0;
						oldMap[0]=0;
						oldMap[1]=0;
						gBackgroundClip.x = 0;
						gBackgroundClip.y = 0;
					break;
					case 2:
						p.setX(25);
						p.setY(902-480);
						myLVL.setlvl(1);
						myLVL.nextLVL();
						map[0]=1;
						map[1]=0;
						oldMap[0]=1;
						oldMap[1]=0;
						gBackgroundClip.x = 0;
						gBackgroundClip.y = 480;
					break;
					case 3:
						p.setX(30);
						p.setY(225);
						myLVL.setlvl(2);
						myLVL.nextLVL();
						map[0]=0;
						map[1]=0;
						oldMap[0]=0;
						oldMap[1]=0;
						gBackgroundClip.x = 0;
						gBackgroundClip.y = 0;
					break;

	
					
				}
				//create first set of walls doors and keys	

				//update walls
				myLVL.updateWalls(map);
					
				//update doors and keys
				myLVL.updateDoors(map); 
				myLVL.updateKeys(map);
				
				enemies.clear();
				//update enemies
				myLVL.updateEnemies(map);
				//create enemies (can't create a vector of enemies inside of Level due to what I believe is caused by header file issues)
				for(int j=0;j<(myLVL.getEnemies()).size();j++){
					enemyX =  myLVL.getEnemies()[j][0];
					enemyY =  myLVL.getEnemies()[j][1];
					enemies.push_back(Enemy(enemyX,enemyY));
				}
				
			while (!over && !dead){
			
	
				//Handle events on queue
				while (SDL_PollEvent(&e) != 0){
					if (e.type == SDL_QUIT){
						over = true;
					}

					//pass events to the player
					p.handleEvent(e);
				}


				p.move(myLVL);	

				//see if next Level has been reached
				if (myLVL.getlvl() == 1){

					//see if player has reached exit
					if (map[0] == 1 && p.getY() >= 475){
						myLVL.setlvl(2);
						dead = true;
						cont = true;
						continue;
					}
				}
				
				if (myLVL.getlvl() == 2){

					//see if player has reached exit
					if (map[0] == 0 && map[1] == 1 && p.getX() >= 635){
						myLVL.setlvl(3);
						dead = true;
						cont = true;
						continue;
					}
				}

				if (myLVL.getlvl() == 3){

					//see if player has reached exit
					if (map[1] == 2 && p.getX() >= 635){
						myLVL.setlvl(4);
						dead = true;
						cont = true;
						over = true;
						continue;
					}
				}
				
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
					myLVL.updateEnemies(map);
					enemies.clear();
					//create enemies (can't create a vector of enemies inside of Level due to what I believe is caused by header file issues)
					for(int j=0;j<(myLVL.getEnemies()).size();j++){
						enemyX =  myLVL.getEnemies()[j][0];
						enemyY =  myLVL.getEnemies()[j][1];
						enemies.push_back(Enemy(enemyX,enemyY));
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
				SDL_RenderClear(gRenderer);
		
				//Render background
				if (myLVL.getlvl() == 1) gLevel1Texture.render(0,0,&gBackgroundClip);
				else if(myLVL.getlvl()==2) gLevel2Texture.render(0,0,&gBackgroundClip);
				else if(myLVL.getlvl()==3) gLevel3Texture.render(0,0,&gBackgroundClip);
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
						myLVL.doorInteract(j,p.getKeys(),map);
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
					//		Mix_PlayChannel(-1,gKey,0);
						}
					}
				}

				

				//Render and update enemies
				for(eiter=enemies.begin();eiter!=enemies.end();++eiter){
					(*eiter).update(myLVL,&p);
					(*eiter).move(myLVL);
					enemyX = (*eiter).getX();
					enemyY = (*eiter).getY();
					sprite = 0;
					//determine which sprite to use
					if ((*eiter).getYVel() == 1){
						sprite = 0 + frame/4;
					}
					else if ((*eiter).getYVel() == -1){
						sprite = 12 + frame/4;
					}
					else if ((*eiter).getXVel() == 1){
						sprite = 8 + frame/4;
					}
					else if ((*eiter).getXVel() == -1){
						sprite = 4 + frame/4;
					}

					else if ((*eiter).getYVel() == 0 && (*eiter).getXVel() == 0) { 
						sprite = 0;
					}
					gEnemyTexture.render(enemyX,enemyY,&gEnemyClips[sprite]);
				}
					
				//Render player
				
				//determine which sprite to use
				if (p.getYVel() == 1){
					sprite = 0 + frame/4;
				}
				else if (p.getYVel() == -1){
					sprite = 12 + frame/4;
				}
				else if (p.getXVel() == 1){
					sprite = 8 + frame/4;
				}
				else if (p.getXVel() == -1){
					sprite = 4 + frame/4;
				}

				else if (p.getYVel() == 0 && p.getXVel() == 0) { 
					sprite = 0;
				}
				gPlayerTexture.render(p.getX(),p.getY(),&gPlayerClips[sprite]);
				
				//make is so blackout moves with character. Need to center field of vision at character center
				gBlackoutTexture.render((-750+PLAYER_WIDTH/2)+p.getX(),(-750+PLAYER_HEIGHT/2)+p.getY());
				//Update screen
				SDL_RenderPresent(gRenderer);

				++frame;
				if (frame > 15) frame = 0;
				//sets dead to true if the character is dead
				if(p.gameOver()){ 
					dead = true;
					//makes velocities *-1 to see it doesn't mess up when keys are released
					p.setYVel(0);
					p.setXVel(0);
					p.setSpeed(5);
					
				}
			}

			if(!over && !cont){
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
				SDL_RenderClear(gRenderer);
		
				//Bring up Game Over Screen	
				gCoverTexture.render(0,0);
				gOverTexture.render(0,0);

				//Update screen
				SDL_RenderPresent(gRenderer);
				while(!over && !cont){
					//Check for user to quit
					while (SDL_PollEvent(&e) != 0){
						if (e.type == SDL_QUIT){
							over = true;
						}
						else if(e.type == SDL_MOUSEBUTTONDOWN){
							//make sure mouse is over continue
							SDL_GetMouseState(&mX,&mY);
							if (mX <= 408 && mX >= 230 && mY <= 413 && mY >= 351){
								//make it so game continues
								cont = true;
								dead = false;

								//reset vars but just reset player health for now
								p.setHealth(3);
	
							}
						}
					}
				}
			}
			}

		if (myLVL.getlvl() == 4){
			//Clear screen
			SDL_SetRenderDrawColor(gRenderer,0xFF,0xFF,0xFF,0xFF);
			SDL_RenderClear(gRenderer);
		
			//Bring up Game Over Screen	
			gWinTexture.render(0,0);

			//Update screen
			SDL_RenderPresent(gRenderer);
			over = false;
			while(!over){
				//Check for user to quit
				while (SDL_PollEvent(&e) != 0){
					if (e.type == SDL_QUIT){
						over = true;
					}

				}
			}	
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


