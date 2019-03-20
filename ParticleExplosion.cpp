// ParticleExplosion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SDL.h>
#include <iostream>
#include "pch.h"
#include "Screen.h"

int main(int argc, char *argv[])  //need to have the parameters for SDL to work
{
	Screen screen;

	if (screen.Init() == false)
	{
		std::cout << "Error Initializing SDL: " << SDL_GetError() << std::endl;
	}

	//when window is created start "Update " loop while quit is false
	while (true)
	{
		//update particles
		//draw particles
		//check for messages/events (key presses, mouse moves, etc.)

		if (screen.ProcessEvents() == false)
		{
			break;  //breaks look if false
		}
		
	}

	screen.Close();

	return 0;
}