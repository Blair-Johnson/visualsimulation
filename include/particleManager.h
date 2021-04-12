#pragma once
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include "particle.h"
#include "window.h"


class ParticleManager {
public:
	ParticleManager(RenderWindow*, int);
	ParticleManager(RenderWindow*, std::vector<Particle>);
	~ParticleManager();
	void zeroForces();
	void zeroForcesThreaded();
	void updateForces();
	void drawNewPos();
	
public:
	void threadZeroRange(Particle*, Particle*);
	std::vector <Particle> particleList;
	RenderWindow* m_window;
	std::mutex m_mutex;

};
