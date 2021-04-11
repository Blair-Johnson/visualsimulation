#include "../include/quadtree.h"

TreeNode::TreeNode(std::vector<Particle*> p_particles) {
	m_particles = p_particles;
	m_com = Eigen::Vector2f(0, 0);
	m_mass = 0;
	float t_mass = 0;

	for (int i = 0; i < m_particles.size(); i++) {
		t_mass = m_particles[i]->getMass();
		m_mass += t_mass;
		m_com += m_particles[i]->getPos() * t_mass;
	}
	m_com /= m_mass;
}

