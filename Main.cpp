#include "Canvas.h"
#include "Image.h"
#include "SDL.h"
#include <iostream>

int main(int, char**)
{
	const unsigned int width = 800;
	const unsigned int height = 600;
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("2D Renderer", 100, 100, 800, 600, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr)
	{
		std::cout << "SDL Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	Canvas canvas(renderer, width, height);
	Image image;
	image.LoadImage("cat.bmp");
	Image image2;
	image2.LoadImage("sus.bmp");
	Image image3;
	image3.LoadImage("color.bmp", 50);

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		SDL_PollEvent(&event);
		switch (event.type)
		{
		case SDL_QUIT:
			quit = true;
			break;
		}
		canvas.Clear({ 0, 0, 0, 255 });
		
		/*
		for (int i = 0; i < 100; i++)
		{
			canvas.DrawPoint({ rand() % width, rand() % height }, { 255, 255, 255, 255 });
		}

		for (int i = 0; i < 100; i++)
		{
			canvas.DrawLine({ rand() % width, rand() % height }, { rand() % width, rand() % height }, { 255, 255, 255, 255 });
		}
		
		for (int i = 0; i < 100; i++)
		{
			canvas.DrawRect({ rand() % width, rand() % height , rand() % width, rand() % height }, { 255, 255, 255, 255 });
		}
		
		for (int i = 0; i < 100; i++)
		{
			canvas.DrawTri({ rand() % width, rand() % height }, { rand() % width, rand() % height }, { rand() % width, rand() % height }, { 255, 255, 255, 255 });
		}
		

		canvas.DrawCircle({ 200, 400 }, 30, { 255, 255, 255, 255 });
		*/

		canvas.DrawImage(&image, { 100, 100 });
		canvas.DrawImage(&image2, { 250, 250 }, {0, 255, 0, 255});
		canvas.DrawImage(&image3, { 300, 300 });
		//canvas.ProcessInvert();
		//canvas.ProcessMonochrome();
		//canvas.ProcessNightVision();
		//canvas.ProcessThreshold({180, 180, 180, 255});
		//canvas.ProcessBrightness(-100);
		//canvas.ProcessColor(50, 50, -100);

		canvas.Update();
		SDL_RenderClear(renderer);
		canvas.Draw(renderer);
		SDL_RenderPresent(renderer);
	}


	SDL_Quit();

	return 0;
}

