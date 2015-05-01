/*
 * Final Project
 * Main driver program
 * Steven Mike & Brian Mann
 */

#ifndef SDLCLASSES_H
#define SDLCLASSES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <cmath>
#include "Player.h"
#include "Level.h"
#include "Person.h"
using namespace std;

Player updateBackground(Player,int[],Level);

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Player dimension constants
const int PLAYER_WIDTH = 30;
const int PLAYER_HEIGHT = 35;

//Door dimension constants
const int DOOR_WIDTH = 20;
const int DOOR_HEIGHT = 40;

//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#ifdef _SDL_TTF_H
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif
		
		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gPlayerTexture;
LTexture gLevel1Texture;
LTexture gLevel2Texture;
LTexture gLevel3Texture;
LTexture gWinTexture;
LTexture gDoorTexture;
LTexture gKeyTexture;
LTexture gEnemyTexture;
LTexture gBlackoutTexture;
LTexture gCoverTexture;
LTexture gTitleTexture;
LTexture gOverTexture;

//sprite clips
SDL_Rect gPlayerClips[16];
SDL_Rect gDoorClips[32];
SDL_Rect gKeyClips[7];
SDL_Rect gEnemyClips[16];

//background clip
SDL_Rect gBackgroundClip;

//The music that will be played
Mix_Music *gMusic = NULL;
Mix_Music *gChase = NULL; 

//Sound effects that will be played
Mix_Chunk *gDoorOpen = NULL;
Mix_Chunk *gKey = NULL;


LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				//Initialize SDL_Mixer
				if( Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT, 2, 2048000) < 0){
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;


	//Load Title and Cover
	if( !gCoverTexture.loadFromFile("images/cover.png")){
		printf( "Failed to load press texture!\n" );
		success = false;
	}
	
	if( !gTitleTexture.loadFromFile("images/title.png")){
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	if( !gWinTexture.loadFromFile("images/win.png")){
		printf( "Failed to load press texture!\n" );
		success = false;
	}
	

	//Load level 1 texture
	if( !gLevel1Texture.loadFromFile( "images/level1.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
	else {
		gBackgroundClip.x=0;
		gBackgroundClip.y=0;
		gBackgroundClip.w=SCREEN_WIDTH;
		gBackgroundClip.h=SCREEN_HEIGHT;
	}
	//Load level 2 texture
	if( !gLevel2Texture.loadFromFile( "images/level2.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}

	//Load level 3 texture
	if( !gLevel3Texture.loadFromFile( "images/level3.png" ) )
	{
		printf( "Failed to load press texture!\n" );
		success = false;
	}
	
	//Load up texture
	if( !gPlayerTexture.loadFromFile( "images/player.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	else {
		gPlayerClips[0].x=2;
		gPlayerClips[0].y=1;
		gPlayerClips[0].w=PLAYER_WIDTH;
		gPlayerClips[0].h=PLAYER_HEIGHT;

		gPlayerClips[1].x=28;
		gPlayerClips[1].y=2;
		gPlayerClips[1].w=PLAYER_WIDTH;
		gPlayerClips[1].h=PLAYER_HEIGHT;

		gPlayerClips[2].x=54;
		gPlayerClips[2].y=1;
		gPlayerClips[2].w=PLAYER_WIDTH;
		gPlayerClips[2].h=PLAYER_HEIGHT;

		gPlayerClips[3].x=81;
		gPlayerClips[3].y=2;
		gPlayerClips[3].w=PLAYER_WIDTH;
		gPlayerClips[3].h=PLAYER_HEIGHT;

		gPlayerClips[4].x=1;
		gPlayerClips[4].y=35;
		gPlayerClips[4].w=PLAYER_WIDTH;
		gPlayerClips[4].h=PLAYER_HEIGHT;

		gPlayerClips[5].x=28;
		gPlayerClips[5].y=35;
		gPlayerClips[5].w=PLAYER_WIDTH;
		gPlayerClips[5].h=PLAYER_HEIGHT;

		gPlayerClips[6].x=53;
		gPlayerClips[6].y=35;
		gPlayerClips[6].w=PLAYER_WIDTH;
		gPlayerClips[6].h=PLAYER_HEIGHT;

		gPlayerClips[7].x=81;
		gPlayerClips[7].y=35;
		gPlayerClips[7].w=PLAYER_WIDTH;
		gPlayerClips[7].h=PLAYER_HEIGHT;

		gPlayerClips[8].x=2;
		gPlayerClips[8].y=68;
		gPlayerClips[8].w=PLAYER_WIDTH;
		gPlayerClips[8].h=PLAYER_HEIGHT;

		gPlayerClips[9].x=28;
		gPlayerClips[9].y=68;
		gPlayerClips[9].w=PLAYER_WIDTH;
		gPlayerClips[9].h=PLAYER_HEIGHT;

		gPlayerClips[10].x=54;
		gPlayerClips[10].y=68;
		gPlayerClips[10].w=PLAYER_WIDTH;
		gPlayerClips[10].h=PLAYER_HEIGHT;

		gPlayerClips[11].x=81;
		gPlayerClips[11].y=68;
		gPlayerClips[11].w=PLAYER_WIDTH;
		gPlayerClips[11].h=PLAYER_HEIGHT;

		gPlayerClips[12].x=2;
		gPlayerClips[12].y=102;
		gPlayerClips[12].w=PLAYER_WIDTH;
		gPlayerClips[12].h=PLAYER_HEIGHT;

		gPlayerClips[13].x=28;
		gPlayerClips[13].y=103;
		gPlayerClips[13].w=PLAYER_WIDTH;
		gPlayerClips[13].h=PLAYER_HEIGHT;

		gPlayerClips[14].x=54;
		gPlayerClips[14].y=102;
		gPlayerClips[14].w=PLAYER_WIDTH;
		gPlayerClips[14].h=PLAYER_HEIGHT;

		gPlayerClips[15].x=81;
		gPlayerClips[15].y=103;
		gPlayerClips[15].w=PLAYER_WIDTH;
		gPlayerClips[15].h=PLAYER_HEIGHT;

	}

	//Load Enemy
	if( !gEnemyTexture.loadFromFile( "images/enemy.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	else {
		gEnemyClips[0].x=38;
		gEnemyClips[0].y=0;
		gEnemyClips[0].w=PLAYER_WIDTH;
		gEnemyClips[0].h=PLAYER_HEIGHT;

		gEnemyClips[1].x=2;
		gEnemyClips[1].y=1;
		gEnemyClips[1].w=PLAYER_WIDTH;
		gEnemyClips[1].h=PLAYER_HEIGHT;

		gEnemyClips[2].x=38;
		gEnemyClips[2].y=0;
		gEnemyClips[2].w=PLAYER_WIDTH;
		gEnemyClips[2].h=PLAYER_HEIGHT;

		gEnemyClips[3].x=74;
		gEnemyClips[3].y=0;
		gEnemyClips[3].w=PLAYER_WIDTH;
		gEnemyClips[3].h=PLAYER_HEIGHT;

		gEnemyClips[4].x=37;
		gEnemyClips[4].y=35;
		gEnemyClips[4].w=PLAYER_WIDTH;
		gEnemyClips[4].h=PLAYER_HEIGHT;

		gEnemyClips[5].x=1;
		gEnemyClips[5].y=36;
		gEnemyClips[5].w=PLAYER_WIDTH;
		gEnemyClips[5].h=PLAYER_HEIGHT;

		gEnemyClips[6].x=37;
		gEnemyClips[6].y=35;
		gEnemyClips[6].w=PLAYER_WIDTH;
		gEnemyClips[6].h=PLAYER_HEIGHT;

		gEnemyClips[7].x=73;
		gEnemyClips[7].y=36;
		gEnemyClips[7].w=PLAYER_WIDTH;
		gEnemyClips[7].h=PLAYER_HEIGHT;

		gEnemyClips[8].x=39;
		gEnemyClips[8].y=71;
		gEnemyClips[8].w=PLAYER_WIDTH;
		gEnemyClips[8].h=PLAYER_HEIGHT;

		gEnemyClips[9].x=3;
		gEnemyClips[9].y=72;
		gEnemyClips[9].w=PLAYER_WIDTH;
		gEnemyClips[9].h=PLAYER_HEIGHT;

		gEnemyClips[10].x=39;
		gEnemyClips[10].y=71;
		gEnemyClips[10].w=PLAYER_WIDTH;
		gEnemyClips[10].h=PLAYER_HEIGHT;

		gEnemyClips[11].x=75;
		gEnemyClips[11].y=72;
		gEnemyClips[11].w=PLAYER_WIDTH;
		gEnemyClips[11].h=PLAYER_HEIGHT;

		gEnemyClips[12].x=38;
		gEnemyClips[12].y=106;
		gEnemyClips[12].w=PLAYER_WIDTH;
		gEnemyClips[12].h=PLAYER_HEIGHT;

		gEnemyClips[13].x=2;
		gEnemyClips[13].y=107;
		gEnemyClips[13].w=PLAYER_WIDTH;
		gEnemyClips[13].h=PLAYER_HEIGHT;

		gEnemyClips[14].x=38;
		gEnemyClips[14].y=106;
		gEnemyClips[14].w=PLAYER_WIDTH;
		gEnemyClips[14].h=PLAYER_HEIGHT;

		gEnemyClips[15].x=74;
		gEnemyClips[15].y=107;
		gEnemyClips[15].w=PLAYER_WIDTH;
		gEnemyClips[15].h=PLAYER_HEIGHT;

	}

	//Load door
	if ( !gDoorTexture.loadFromFile("images/door.png")){
		printf("Failed to load up texture!\n");
		success = false;
	}
	else{

		gDoorClips[0].x=90;
		gDoorClips[0].y=0;
		gDoorClips[0].w=DOOR_WIDTH;
		gDoorClips[0].h=DOOR_HEIGHT;
	
		gDoorClips[3].x=90;
		gDoorClips[3].y=120;
		gDoorClips[3].w=DOOR_WIDTH;
		gDoorClips[3].h=DOOR_HEIGHT;
	
		gDoorClips[4].x=60;
		gDoorClips[4].y=0;
		gDoorClips[4].w=DOOR_WIDTH;
		gDoorClips[4].h=DOOR_HEIGHT;
	
		gDoorClips[7].x=60;
		gDoorClips[7].y=120;
		gDoorClips[7].w=DOOR_WIDTH;
		gDoorClips[7].h=DOOR_HEIGHT;
	
		gDoorClips[8].x=30;
		gDoorClips[8].y=0;
		gDoorClips[8].w=DOOR_WIDTH;
		gDoorClips[8].h=DOOR_HEIGHT;
	
		gDoorClips[11].x=30;
		gDoorClips[11].y=120;
		gDoorClips[11].w=DOOR_WIDTH;
		gDoorClips[11].h=DOOR_HEIGHT;
	
		gDoorClips[12].x=0;
		gDoorClips[12].y=0;
		gDoorClips[12].w=DOOR_WIDTH;
		gDoorClips[12].h=DOOR_HEIGHT;
	
		gDoorClips[15].x=0;
		gDoorClips[15].y=120;
		gDoorClips[15].w=DOOR_WIDTH;
		gDoorClips[15].h=DOOR_HEIGHT;
	
		gDoorClips[16].x=90;
		gDoorClips[16].y=160;
		gDoorClips[16].w=DOOR_WIDTH;
		gDoorClips[16].h=DOOR_HEIGHT;
	
		gDoorClips[19].x=90;
		gDoorClips[19].y=280;
		gDoorClips[19].w=DOOR_WIDTH;
		gDoorClips[19].h=DOOR_HEIGHT;
	
		gDoorClips[20].x=60;
		gDoorClips[20].y=160;
		gDoorClips[20].w=DOOR_WIDTH;
		gDoorClips[20].h=DOOR_HEIGHT;
	
		gDoorClips[23].x=60;
		gDoorClips[23].y=280;
		gDoorClips[23].w=DOOR_WIDTH;
		gDoorClips[23].h=DOOR_HEIGHT;
	
		gDoorClips[24].x=30;
		gDoorClips[24].y=160;
		gDoorClips[24].w=DOOR_WIDTH;
		gDoorClips[24].h=DOOR_HEIGHT;
	
		gDoorClips[27].x=30;
		gDoorClips[27].y=280;
		gDoorClips[27].w=DOOR_WIDTH;
		gDoorClips[27].h=DOOR_HEIGHT;
	
		gDoorClips[28].x=0;
		gDoorClips[28].y=160;
		gDoorClips[28].w=DOOR_WIDTH;
		gDoorClips[28].h=DOOR_HEIGHT;
	
		gDoorClips[31].x=0;
		gDoorClips[31].y=280;
		gDoorClips[31].w=DOOR_WIDTH;
		gDoorClips[31].h=DOOR_HEIGHT;
	
	}

	//Load keys
	if( !gKeyTexture.loadFromFile("images/key.png")){
		printf("Failed to load up texture!\n");
		success = false;
	}	
	else{ 

		//load clips
		gKeyClips[0].x=0;
		gKeyClips[0].y=58;
		gKeyClips[0].w=30;
		gKeyClips[0].h=13;

		gKeyClips[1].x=0;
		gKeyClips[1].y=29;
		gKeyClips[1].w=30;
		gKeyClips[1].h=13;

		gKeyClips[2].x=0;
		gKeyClips[2].y=0;
		gKeyClips[2].w=30;
		gKeyClips[2].h=14;

		gKeyClips[3].x=0;
		gKeyClips[3].y=72;
		gKeyClips[3].w=30;
		gKeyClips[3].h=13;

		gKeyClips[4].x=0;
		gKeyClips[4].y=87;
		gKeyClips[4].w=30;
		gKeyClips[4].h=13;

		gKeyClips[5].x=0;
		gKeyClips[5].y=43;
		gKeyClips[5].w=30;
		gKeyClips[5].h=13;

		gKeyClips[6].x=0;
		gKeyClips[6].y=15;
		gKeyClips[6].w=30;
		gKeyClips[6].h=13;
	}

	
	//Load up blackout (field of vision)
	if( !gBlackoutTexture.loadFromFile( "images/blackout.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}

	//Load Game Over
	if( !gOverTexture.loadFromFile( "images/gameOver.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	

	//Load music
//	gMusic = Mix_LoadMUS("DoorOpen.wav");
	if (gMusic == NULL){
	//	printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError() );
       // success = false;
    	}

//	gChase = Mix_LoadMUS("sounds/Chase.wav");
	if (gChase == NULL){
//		printf("Failed to load chase music! SDL_mixer Error: %s\n", Mix_GetError() );
  //      success = false;
    	}

	//Load Sound Effects
	gDoorOpen = Mix_LoadWAV("sounds/DoorOpen.wav");
	if (gDoorOpen == NULL){
		printf("Failed to load door sfx! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    	}

	gKey = Mix_LoadWAV("sounds/Key.wav");
	if (gKey == NULL){
		printf("Failed to load key sfx! SDL_mixer Error: %s\n", Mix_GetError() );
        success = false;
    	}

	return success;
}

void close()
{
	//Free loaded images
	gCoverTexture.free();
	gTitleTexture.free();
	gLevel1Texture.free();
	gLevel2Texture.free();
	gLevel3Texture.free();
	gPlayerTexture.free();
	gBlackoutTexture.free();
	gDoorTexture.free();
	gKeyTexture.free();
	gEnemyTexture.free();
	gOverTexture.free();
	gWinTexture.free();

	//Free sound effects
	Mix_FreeChunk(gKey);
	Mix_FreeChunk(gDoorOpen);
	gKey = NULL;
	gDoorOpen = NULL;

	//Free music
	Mix_FreeMusic(gMusic);
	Mix_FreeMusic(gChase);
	gMusic = NULL;
	gChase = NULL;
	
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

#endif
