#pragma once
#include <vector>
#include "particle.h"
#include "window.h"


class ParticleManager {
public:
	ParticleManager(RenderWindow*, int);
	ParticleManager(RenderWindow*, std::vector<Particle>);
	void zeroForces();
	void updateForces();
	void drawNewPos();
	
public:
	std::vector <Particle> particleList;
	RenderWindow* m_window;

};