// ParticleExplosion.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"  //pre-compiled headers need to be at the top
#include <iostream>
#include <math.h>
#include <time.h>
#include "Screen.h"
#include "Swarm.h"

int main(int argc, char *argv[])  //need to have the parameters for SDL to work
{
	srand((unsigned)time(NULL));

	Screen screen;

	if (screen.Init() == false)
	{
		std::cout << "Error Initializing SDL: " << SDL_GetError() << std::endl;
	}

	Swarm swarm;

	//when window is created start "Update " loop while quit is false
	while (true)
	{
		//update particles

		//draw particles
		
		int elapsedTime = SDL_GetTicks();  //gets ticks or frames ran after the program has started


		//screen.ClearScreen();  //clears screen every frame
		swarm.Update(elapsedTime);  //updates particles

		//sin(elapsedTime * .001)  returns numbers from 0 - 1
		//by add 1 + sin(elapsedTime * .001) it will go from 0 - 2
		//then by multiplying (1 + sin(elapsedTime * .001)) * 128 will cycle up to a max of 255 which is what we want
		double red = (1 + sin(elapsedTime * .0002)) * 128; 
		double green = (1 + sin(elapsedTime * .0001)) * 128; 
		double blue = (1 + sin(elapsedTime * .0003)) * 128; 

		const Particle *const pParticles = swarm.GetParticles();  //gets a pointer to getparticles function
			   
		//cycles through the particle array
		for (int i = 0; i < Swarm::NPARTICLES; i++)
		{
			Particle particle = pParticles[i];  //creates a variable to hold the particles to cycle through them

			//should be center of screen
			int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2; //we add one so that x is between 0 and 2 and divide by 2 for half the screen
			int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2; //we add one so that x is between 0 and 2 and divide by 2 for half the screen
		
			screen.SetPixel(x, y, red, green, blue);
		}

		//implementing a blox blur
		screen.BoxBlur();

		//update/Draw the screen every frame
		screen.Update();

		//check for messages/events (key presses, mouse moves, etc.)
		if (screen.ProcessEvents() == false)
		{
			break;  //breaks look if false
		}
		
	}

	screen.Close();

	return 0;
}