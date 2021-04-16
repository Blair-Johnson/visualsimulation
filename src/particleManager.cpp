# include "../include/particleManager.h"

ParticleManager::ParticleManager(RenderWindow* p_window, int p_numParticles)
	:m_window(p_window), m_quadtree(m_window->getWidth(), m_window->getHeight())
{
	int radius = 3;
	int m = 1;
	
	//std::cout << m_quadtree.headNode << std::endl;
	//std::cout << m_quadtree.headNode << std::endl;
	for (int i = 0; i < p_numParticles; i++) {
		float x = rand() % (m_window->getWidth() - 1 - 2 * radius) + radius;
		float y = rand() % (m_window->getHeight() - 1 - 2 * radius) + radius;
		Eigen::Vector2f t_pos = Eigen::Vector2f(x, y);
		Eigen::Vector2f t_vel = Eigen::Vector2f::Random() * 1000;
		Particle t_particle = Particle(m_window->getRenderer(), t_pos, t_vel, m, radius);
		particleList.push_back(t_particle);
		m_quadtree.pushElement(&t_particle, t_particle);
	}

	m_quadtree.initHeadNode();

	//std::cout << m_quadtree.headNode->headNode << std::endl;
}

ParticleManager::ParticleManager(RenderWindow* p_window, std::vector<Particle> p_particleList)
	:m_window(p_window), particleList(p_particleList)
{
	QuadTree m_quadtree(m_window->getWidth(), m_window->getHeight());
	indexElements();
}

ParticleManager::~ParticleManager() {}

void ParticleManager::indexElements() {
	for (int i = 0; i < particleList.size(); ++i) {
		m_quadtree.pushElement(&particleList[i], particleList[i]);
	}
}

void ParticleManager::zeroForcesThreaded() {
	int length = particleList.size();
	if (length > 40){
		int per_thread = length / 4;
		Particle *s1, *e1, *s2, *e2, *s3, *e3, *s4, *e4;
		s1 = &particleList.front();
		e1 = s1 + per_thread;
		s2 = e1;
		e2 = s2 + per_thread;
		s3 = e2;
		e3 = s3 + per_thread;
		s4 = e3;
		e4 = &particleList.back() + 1;
		std::thread thread1(&ParticleManager::threadZeroRange, this, s1, e1);
		std::thread thread2(&ParticleManager::threadZeroRange, this, s2, e2);
		std::thread thread3(&ParticleManager::threadZeroRange, this, s3, e3);
		std::thread thread4(&ParticleManager::threadZeroRange, this, s4, e4);
		thread1.join();
		thread2.join();
		thread3.join();
		thread4.join();
	}
}

void ParticleManager::threadZeroRange(Particle* p_begin, Particle* p_end) {
	for (auto ptr = p_begin; ptr != p_end; ++ptr) {
		ptr->zeroFnet();
	}
}

void ParticleManager::zeroForces() {
	for (int i = 0; i < particleList.size(); i++) {
		particleList[i].zeroFnet();
	}
}

void ParticleManager::updateForces(Particle p_mouse, int atr, int mouse_atr, float interaction_coeff, float mouse_interaction_coeff, float min_interaction_dist) {
	//for (int i = 0; i < particleList.size(); ++i) {
	//	particleList[i].updateFnet(&p_mouse, mouse_atr, mouse_interaction_coeff, min_interaction_dist);
	//	for (int j = i + 1; j < particleList.size(); j++)
	//		particleList[i].updateFnet(&particleList[j], atr, interaction_coeff, min_interaction_dist);
	//}
	m_quadtree.updateForces(atr, interaction_coeff, min_interaction_dist);
}

void ParticleManager::updateStep(float dt, int gravity, float damping) {
	for (int i = 0; i < particleList.size(); ++i) {
		particleList[i].step(0.01, gravity, damping);
		particleList[i].checkLimits(m_window->getWidth() - 1, m_window->getHeight() - 1);
	}
}

void ParticleManager::renderParticles() {
	for (int i = 0; i < particleList.size(); ++i) {
		particleList[i].render();
	}
}

void ParticleManager::redistributeQuadtree() {
	m_quadtree.distribute();
}