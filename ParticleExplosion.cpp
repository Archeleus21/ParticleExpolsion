// ParticleExplosion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[])  //need to have the parameters for SDL to work
{
	//sets window width and height
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)  //all error will be negative
	{
		//prints couldnt initialize along with the error
		std::cout << "SDL could not be initialized!  SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//points to and creates a window
	SDL_Window *window = SDL_CreateWindow("Particle Fire Explosion", 
										   SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
										   SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//checks if able to create window
	if (window == NULL)
	{
		SDL_Quit();
		return 2;
	}
	//creates renderer and texture variables
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC); //SDL_RENDERER_PRESENTVSYNC, keeps screen in sync to prevent shearing
	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);  //SDL_PIXELFORMAT_RGBA8888, allows up to 255 per RGB value																																  
			
	if (renderer == NULL)
	{
		std::cout << "Could not create renderer!" << std::endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 3;
	}

	if (texture == NULL)
	{
		std::cout << "Could not create texture!" << std::endl;
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return 4;
	}

	Uint32 *buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];  //stores memory for pixels

	//set a block of memory with a particular value (255 = 0xFF in hex = 1 byte)
	memset(buffer, 0xFF, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH * sizeof(Uint32));  //updates the texture, the stored memory or buffer, then the width of the screen * the size of the memory allocated per pixel
	SDL_RenderClear(renderer); //clears renderer
	SDL_RenderCopy(renderer, texture, NULL, NULL);  //passes renderer
	SDL_RenderPresent(renderer);  //display renderer

	//when window is created start "Update " loop while quit is false
	bool quit = false;

	SDL_Event event; //variable to look for events
	while (!quit)
	{
		//update particles
		//draw particles
		//check for messages/events (key presses, mouse moves, etc.)

		while (SDL_PollEvent(&event))  //looks for events, you pass in the address of the variable created
		{
			if (event.type == SDL_QUIT)  //looks for the quit bool to change to true
			{
				quit = true;
			}
		}
	}

	delete[] buffer;  //frees memory resources used for the buffer
	SDL_DestroyRenderer(renderer);  //destroys renderer
	SDL_DestroyTexture(texture);  //destroys texture
	//destroys window before quiting if window was created.
	SDL_DestroyWindow(window);
	//quits
	SDL_Quit();

	return 0;
}