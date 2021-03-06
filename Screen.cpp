#include "pch.h"
#include "Screen.h"


Screen::Screen() 
	:	m_window(NULL),
		m_renderer(NULL),
		m_texture(NULL),
		m_buffer1(NULL),
		m_buffer2(NULL)
{

}


Screen::~Screen()
{

}

bool Screen::Init()
{

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)  //all error will be negative
	{
		//prints couldnt initialize along with the error
		return false;
	}

	//points to and creates a window
	m_window = SDL_CreateWindow("Particle Fire Explosion",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	//checks if able to create window
	if (m_window == NULL)
	{
		SDL_Quit();
		return false;
	}
	//creates renderer and texture variables
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC); //SDL_RENDERER_PRESENTVSYNC, keeps screen in sync to prevent shearing
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);  //SDL_PIXELFORMAT_RGBA8888, allows up to 255 per RGB value																																  

	if (m_renderer == NULL)
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	if (m_texture == NULL)
	{
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];  //stores memory for pixels
	m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];  //stores memory for pixels

	//set a block of memory with a particular value (255 = 0xFF in hex = 1 byte)
	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

	/*
	buffer[30000] = 0xFFFFFF;  // 0xFF = white or 255 or max value a byte can have
							   // 0xRGBA or 0xFFFFFFFF or 255, 255, 255, 255
							   
	//loop to change every pixel on screen
	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++)
	{
		m_buffer[i] = 0xFF00FFFF;  //color 0x"R""G""B""A" or 0x00000000 hex goes from 0-F with 8 being half strength.
	}
	*/

	return true;
}

bool Screen::ProcessEvents()
{
	SDL_Event event; //variable to look for events

	while (SDL_PollEvent(&event))  //looks for events, you pass in the address of the variable created
	{
		if (event.type == SDL_QUIT)  //looks for the quit bool to change to true
		{
			return false;
		}
	}

	return true;
}

void Screen::Close()
{
	delete[] m_buffer1;  //frees memory resources used for the buffer
	delete[] m_buffer2;  //frees memory resources used for the buffer
	SDL_DestroyRenderer(m_renderer);  //destroys renderer
	SDL_DestroyTexture(m_texture);  //destroys texture
	//destroys window before quiting if window was created.
	SDL_DestroyWindow(m_window);
	//quits
	SDL_Quit();

}

void Screen::SetPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)	
{

	//will not print pixel off screen
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
	{
		return;
	}

	Uint32 color = 0;

	color += red;
	color <<= 8;
	color += green;
	color <<= 8;
	color += blue;
	color <<= 8;
	color += 0xFF;

	m_buffer1[(y * SCREEN_WIDTH) + x] = color;
}

void Screen::Update()
{	
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));  //updates the texture, the stored memory or buffer, then the width of the screen * the size of the memory allocated per pixel
	SDL_RenderClear(m_renderer); //clears renderer
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);  //passes renderer
	SDL_RenderPresent(m_renderer);  //display renderer
}

//void Screen::ClearScreen()
//{
//	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
//	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
//}

void Screen::BoxBlur()
{
	//swap buffers so pixel info is in m_buffer2 and we are drawing to m_buffer1
	Uint32 *temp = m_buffer1;  //stores what m_buffer1 is pointing at

	m_buffer1 = m_buffer2;  //stores what m_buffer2 is pointer at
	m_buffer2 = temp;  //m_buffer2 is now what m_buffer1 used to be before changing

	for (int y = 0; y < SCREEN_HEIGHT; y++)  //goes over each pixel in each column
	{
		for (int x = 0; x < SCREEN_WIDTH; x++)  //goes through each pixel in each row
		{
			/*
			*Box Blur:
			*need to take center pixel, add all pixel color values
			*get the average and set it to the center pixel's color value
			* 0 0 0 (-1 position)
			* 0 1 0 (0 position)
			* 0 0 0 (1 position)
		   *(-1 0 1)
		   *(Positions)
 			*/

			//stores total color value for each color
			int redTotal = 0;
			int greenTotal = 0;
			int blueTotal = 0;

			//iterates through the rows
			for (int row = -1; row <= 1; row++)
			{
				//iteratea through the columns
				for (int col = -1; col <= 1; col++)
				{
					int currentX = x + col;  //takes x and adds it to the col
					int currentY = y + row; //takes y and adds it to the row

					//checks if pixel is on screen and if so gets color value
					if (currentX >= 0 && currentX < SCREEN_WIDTH  && currentY >= 0 && currentY < SCREEN_HEIGHT)
					{
						//sets color value
						Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];
						
						//gets each color 8 bit color value
						Uint8 red = color >> 24;
						Uint8 green = color >> 16;
						Uint8 blue = color >> 8;

						//adds to totals
						redTotal += red;
						greenTotal += green;
						blueTotal += blue;
					}
				}
			}

			//gets averages
			Uint8 red = redTotal / 9;
			Uint8 green = greenTotal / 9;
			Uint8 blue = blueTotal / 9;

			//sets pixel colors
			SetPixel(x, y, red, green, blue);

		}
	}
}