#include <iostream>
#include "../include/window.h"

RenderWindow::RenderWindow(const char* title, int w, int h)
	:window(NULL), renderer(NULL)
{
	this->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w, h,
		SDL_WINDOW_SHOWN);

	if (window == NULL)
		std::cout << "Window failed to init, error: " << SDL_GetError() << std::endl;

	this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(this->window);
}

void RenderWindow::setColor(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(this->renderer, r, g, b, a);
	SDL_RenderClear(this->renderer);
	SDL_RenderPresent(this->renderer);
}