#pragma once
#include <vector>
#include <thread>
#include <iostream>

#include "particle.h"
#include "window.h"
#include "quadtree.h"


class ParticleManager {
public:
	ParticleManager(RenderWindow*, int);
	ParticleManager(RenderWindow*, std::vector<Particle>);
	~ParticleManager();
	void zeroForces();
	void zeroForcesThreaded();
	void updateStep(float, int, float);
	void renderParticles();
	void updateForces(Particle, int, int, float, float, float);
	void redistributeQuadtree();
	void indexElements();
	
public:
	void threadZeroRange(Particle*, Particle*);
	std::vector <Particle> particleList;
	RenderWindow* m_window;
	QuadTree m_quadtree;

};
