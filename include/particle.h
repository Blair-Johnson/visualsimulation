#pragma once
#include <Eigen/Dense>
#include <SDL.h>

class Particle {
public:
	Particle(Eigen::Vector2f pos, Eigen::Vector2f vel, float m);
private:
	Eigen::Vector2f pos;
	Eigen::Vector2f vel;
	Eigen::Vector2f m;
};