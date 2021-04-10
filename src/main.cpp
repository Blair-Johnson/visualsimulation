#include <iostream>
#include <SDL.h>
#include <time.h>
#include <vector>
#include <chrono>

#include "../include/window.h"
#include "../include/particle.h"

int main(int argc, char* args[]) {
	int WINDOW_W = 1280;
	int WINDOW_H = 720;
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL init failed, error: " << SDL_GetError() << std::endl;

	RenderWindow window("Particle Sim v0.1", WINDOW_W, WINDOW_H);
	window.setColor(48, 48, 48, 255);

	// random seed
	srand(time(NULL));
	// start time
	auto start = std::chrono::steady_clock::now();

	bool running = true;
	SDL_Event event;

	// init 100 random particles
	std::vector<Particle> particleList;
	int radius = 3;
	int numParticles = 1000;
	for (int i = 0; i < numParticles; i++) {
		float x = rand() % (WINDOW_W - 1 - 2 * radius) + radius;
		float y = rand() % (WINDOW_H - 1 - 2 * radius) + radius;
		Eigen::Vector2f t_pos = Eigen::Vector2f( x, y );
		Particle t_particle = Particle(window.getRenderer(), t_pos, t_pos, 10.0, radius);
		particleList.push_back(t_particle);
	}

	for (int i = 0; i < numParticles; i++) {
		particleList[i].render();
	}
	window.update();
	auto end = std::chrono::steady_clock::now();
	

	std::cout << "Drawing Took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	
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