#include <iostream>
#include <SDL.h>

#include "../include/window.h"

int main(int argc, char* args[]) {
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL init failed, error: " << SDL_GetError() << std::endl;

	RenderWindow window("Particle Sim v0.1", 1280, 720);
	window.setColor(48, 48, 48, 255);

	bool running = true;
	SDL_Event event;

	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				running = false;
		}
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}