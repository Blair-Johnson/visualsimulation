#include <iostream>
#include "../include/window.h"

RenderWindow::RenderWindow(const char* p_title, int p_w, int p_h)
	:m_window(NULL), m_renderer(NULL), m_width(p_w), m_height(p_h)
{
	m_window = SDL_CreateWindow(p_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, p_w, p_h,
		SDL_WINDOW_SHOWN);

	if (m_window == NULL)
		std::cout << "Window failed to init, error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(m_window);
}

void RenderWindow::setColor(int p_r, int p_g, int p_b, int p_a) {
	SDL_SetRenderDrawColor(m_renderer, p_r, p_g, p_b, p_a);
}

void RenderWindow::renderClear() {
	SDL_RenderClear(m_renderer);
}

void RenderWindow::update() {
	SDL_RenderPresent(m_renderer);
}

SDL_Renderer* RenderWindow::getRenderer() {
	return m_renderer;
}

int RenderWindow::getWidth() {
	return m_width;
}

int RenderWindow::getHeight() {
	return m_height;
}