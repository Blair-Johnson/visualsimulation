# include "../include/particleManager.h"

ParticleManager::ParticleManager(RenderWindow* p_window, int p_numParticles)
	:m_window(p_window)
{
	int radius = 3;
	int m = 1;

	for (int i = 0; i < p_numParticles; i++) {
		float x = rand() % (m_window->getWidth() - 1 - 2 * radius) + radius;
		float y = rand() % (m_window->getHeight() - 1 - 2 * radius) + radius;
		Eigen::Vector2f t_pos = Eigen::Vector2f(x, y);
		Eigen::Vector2f t_vel = Eigen::Vector2f::Random() * 1000;
		Particle t_particle = Particle(m_window->getRenderer(), t_pos, t_vel, m, radius);
		particleList.push_back(t_particle);
	}
}