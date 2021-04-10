#include <iostream>
#include <SDL.h>
#include <time.h>
#include <vector>
#include <chrono>
#include <Windows.h>

#include "../include/window.h"
#include "../include/particle.h"

int main(int argc, char* args[]) {
	int WINDOW_W = 1280;
	int WINDOW_H = 720;
	if (SDL_Init(SDL_INIT_VIDEO) > 0)
		std::cout << "SDL init failed, error: " << SDL_GetError() << std::endl;

	RenderWindow window("Particle Sim v0.1", WINDOW_W, WINDOW_H);

	// random seed
	srand(time(NULL));

	bool running = true;
	SDL_Event event;

	// init 100 random particles
	std::vector<Particle> particleList;
	int radius = 3;
	int numParticles = 60;
	for (int i = 0; i < numParticles; i++) {
		float x = rand() % (WINDOW_W - 1 - 2 * radius) + radius;
		float y = rand() % (WINDOW_H - 1 - 2 * radius) + radius;
		int m = 1;
		//if (i % 2 == 0) {
		//	m *= -1;
		//}
		Eigen::Vector2f t_pos = Eigen::Vector2f( x, y );
		Eigen::Vector2f t_vel = Eigen::Vector2f::Random()*1000;
		Particle t_particle = Particle(window.getRenderer(), t_pos, t_vel, m, radius);
		particleList.push_back(t_particle);
	}

	auto start = std::chrono::steady_clock::now();
	for (int i = 0; i < numParticles; i++) {
		particleList[i].render();
	}
	window.update();
	auto end = std::chrono::steady_clock::now();
	

	//std::cout << "Drawing Took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	
	while (running) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT)
				running = false;
		}
		auto lstart = std::chrono::steady_clock::now();
		window.renderClear();
		window.setColor(48, 48, 48, 255);
		for (int i = 0; i < numParticles; i++) {
			particleList[i].zeroFnet();
		}
		for (int i = 0; i < numParticles; i++) {
			for (int j = i+1; j < numParticles; j++)
				particleList[i].updateFnet(&particleList[j]);
		}
		for (int i = 0; i < numParticles; i++) {
			particleList[i].step(0.01);
			particleList[i].checkLimits(1280 - 1, 720 - 1);
			particleList[i].render();
		}
		//Sleep(5);
		window.update();
		auto stop = std::chrono::steady_clock::now();
		//std::cout << "Loop: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - lstart).count() << "ms" << std::endl;
	}

	window.cleanUp();
	SDL_Quit();

	return 0;
}