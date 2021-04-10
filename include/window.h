#pragma once
#include <SDL.h>

class RenderWindow
{
public:
	RenderWindow(const char*, int, int);
	void setColor(int, int, int, int);
	SDL_Renderer* getRenderer();
	void update();
	void cleanUp();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
};

