#include <iostream>
#include <SDL.h>
#include <time.h>
#include <vector>
#include <chrono>
#include <Windows.h>

#include "../include/window.h"
#include "../include/particle.h"
#include "../include/particleManager.h"

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

	// init random particles in manager
	int numParticles = 70;
	ParticleManager manager(&window, numParticles);

	manager.redistributeQuadtree();

	manager.zeroForces();

	//auto start = std::chrono::steady_clock::now();
	//for (int i = 0; i < numParticles; i++) {
	//	manager.particleList[i].render();
	//}
	//window.update();
	//auto end = std::chrono::steady_clock::now();

	//Particle mouse_point = Particle(window.getRenderer(), Eigen::Vector2f(0,0), Eigen::Vector2f(0,0), 10, 3);
	//

	////std::cout << "Drawing Took: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms" << std::endl;
	//// coefficients
	//int atr = 1;
	//int mouse_atr = 1;
	//int mouse_x, mouse_y = 0;
	//bool gravity = false;
	//float damping = 0.5;
	//float interaction_coeff = 0.5e6;
	//float mouse_interaction_coeff = 0.5e6;
	//float min_interaction_dist = 3;


	//while (running) {
	//	while (SDL_PollEvent(&event)) {
	//		switch (event.type) {
	//		case SDL_QUIT:
	//			running = false;
	//		case SDL_KEYDOWN: {
	//			switch (event.key.keysym.sym) {
	//			case SDLK_a: {
	//				atr = 1;
	//				std::cout << "Attract" << std::endl;
	//				break;
	//			}
	//			case SDLK_r: {
	//				atr = -1;
	//				std::cout << "Repel" << std::endl;
	//				break;
	//			}
	//			case SDLK_g: {
	//				gravity = !gravity;
	//				std::cout << "Gravity: " << gravity << std::endl;
	//				break;
	//			}
	//			case SDLK_d: {
	//				damping += 0.1;
	//				std::cout << "+Damping: " << damping << std::endl;
	//				break;
	//			}
	//			case SDLK_v: {
	//				if (damping - 0.1 >= 0) {
	//					damping -= 0.1;
	//				}
	//				std::cout << "-Damping: " << damping << std::endl;
	//				break;
	//			}
	//			case SDLK_k: {
	//				interaction_coeff += 1e5;
	//				std::cout << "+Interaction Coeff: " << interaction_coeff << std::endl;
	//				break;
	//			}
	//			case SDLK_m: {
	//				if (interaction_coeff - 1e5 >= 0) {
	//					interaction_coeff -= 1e5;
	//				}
	//				std::cout << "-Interaction Coeff: " << interaction_coeff << std::endl;
	//				break;
	//			}
	//			case SDLK_c: {
	//				mouse_atr *= -1;
	//				std::cout << "Toggle Mouse Attract" << std::endl;
	//				break;
	//			}
	//			case SDLK_x: {
	//				if (mouse_interaction_coeff - 1e5 >= 0) {
	//					mouse_interaction_coeff -= 1e5;
	//				}
	//				std::cout << "-Mouse Interaction Coeff: " << mouse_interaction_coeff << std::endl;
	//				break;
	//			}
	//			case SDLK_z: {
	//				mouse_interaction_coeff += 1e5;
	//				std::cout << "+Mouse Interaction Coeff: " << mouse_interaction_coeff << std::endl;
	//				break;
	//			}
	//			case SDLK_DOWN: {
	//				if (min_interaction_dist - 0.1 >= 0) {
	//					min_interaction_dist -= 0.1;
	//				}
	//				std::cout << "-Min Interaction Dist: " << min_interaction_dist << std::endl;
	//				break;
	//			}
	//			case SDLK_UP: {
	//				min_interaction_dist += 0.1;
	//				std::cout << "+Min Interaction Dist: " << min_interaction_dist << std::endl;
	//				break;
	//			}
	//			default:
	//				break;
	//			}
	//			break;
	//		}
	//		default:
	//			break;
	//		}
	//	}
	//	
	//	SDL_GetMouseState(&mouse_x, &mouse_y);
	//	mouse_point.setPos(Eigen::Vector2f(mouse_x, mouse_y));
	//	auto lstart = std::chrono::steady_clock::now();
	//	manager.redistributeQuadtree();
	//	manager.zeroForces();
	//	//auto l1 = std::chrono::steady_clock::now();
	//	//manager.zeroForcesThreaded();
	//	//auto l2 = std::chrono::steady_clock::now();
	//	//std::cout << "Unthreaded: " << std::chrono::duration_cast<std::chrono::milliseconds>(lstart - l1).count() << "ms" << std::endl;
	//	//std::cout << "Threaded: " << std::chrono::duration_cast<std::chrono::milliseconds>(l2 - l1).count() << "ms" << std::endl;

	//	manager.updateForces(mouse_point, atr, mouse_atr, interaction_coeff, mouse_interaction_coeff, min_interaction_dist);

	//	window.renderClear();
	//	window.setColor(48, 48, 48, 255);
	//	manager.updateStep(0.01, gravity, damping);
	//	auto rdrstart = std::chrono::steady_clock::now();
	//	manager.renderParticles();
	//	window.update();
	//	auto stop = std::chrono::steady_clock::now();
	//	//std::cout << "Calculations: " << std::chrono::duration_cast<std::chrono::milliseconds>(rdrstart - lstart).count() << "ms" << std::endl;
	//	//std::cout << "Render: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - rdrstart).count() << "ms" << std::endl;
	//}

	window.cleanUp();
	SDL_Quit();

	return 0;
}