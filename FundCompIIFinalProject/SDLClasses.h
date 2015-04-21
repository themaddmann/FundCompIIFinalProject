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
LTexture gBackTexture;
LTexture gDoorTexture;
LTexture gKeyTexture;
LTexture gEnemyTexture;
LTexture gBlackoutTexture;
//sprite clips
SDL_Rect gPlayerClips[16];
SDL_Rect gDoorClips[32];
SDL_Rect gKeyClips[7];
SDL_Rect gEnemyClips[16];

//background clip
SDL_Rect gBackgroundClip;

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
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
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
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_SOFTWARE );
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
			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load press texture
	if( !gBackTexture.loadFromFile( "images/level0.png" ) )
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
	
	//Load up texture
	if( !gPlayerTexture.loadFromFile( "images/player.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	else {
		gPlayerClips[0].x=0;
		gPlayerClips[0].y=0;
		gPlayerClips[0].w=PLAYER_WIDTH;
		gPlayerClips[0].h=PLAYER_HEIGHT;
	}

	//Load Enemy
	if( !gEnemyTexture.loadFromFile( "images/player.png" ) )
	{
		printf( "Failed to load up texture!\n" );
		success = false;
	}
	else {
		gEnemyClips[0].x=0;
		gEnemyClips[0].y=0;
		gEnemyClips[0].w=PLAYER_WIDTH;
		gEnemyClips[0].h=PLAYER_HEIGHT;
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

	return success;
}

void close()
{
	//Free loaded images
	gBackTexture.free();
	gPlayerTexture.free();
	gBlackoutTexture.free();
	gDoorTexture.free();
	gKeyTexture.free();
	gEnemyTexture.free();
	
	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

#endif
