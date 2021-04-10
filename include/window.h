#pragma once
#include <SDL.h>

class RenderWindow
{
public:
	RenderWindow(const char* title, int w, int h);
	void setColor(int r, int g, int b, int a);
	void cleanUp();
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};

