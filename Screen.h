#pragma once
#include <SDL.h>
#include <iostream>

class Screen
{
private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;

public:
	//sets window width and height
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGHT = 600;

public:
	Screen();
	~Screen();
	bool Init();
	bool ProcessEvents();
	void Close();

};

