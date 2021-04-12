#pragma once
#include <SDL.h>

class RenderWindow
{
public:
	RenderWindow(const char*, int, int);
	~RenderWindow();
	void setColor(int, int, int, int);
	SDL_Renderer* getRenderer();
	void update();
	void cleanUp();
	void renderClear();
	int getWidth();
	int getHeight();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	int m_height;
	int m_width;
};

