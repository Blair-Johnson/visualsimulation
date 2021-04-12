#include "../include/quadtree.h"

TreeNode::TreeNode(std::vector<Particle*> p_particles, std::tuple<float,float>px_interval,std::tuple<float,float>py_interval)
	:m_particles(p_particles), x_interval(px_interval),y_interval(py_interval), m_mass(0)
{
	findCenter();
}

void TreeNode::findCenter() {
	if (m_particles.size() > 0) {
		m_com[0] = 0;
		m_com[1] = 0;
		m_mean[0] = 0;
		m_mean[1] = 0;
		m_mass = 0;
		float t_mass = 0;

		for (int i = 0; i < m_particles.size(); i++) {
			t_mass = m_particles[i]->getMass();
			m_mass += t_mass;
			m_com += m_particles[i]->getPos() * t_mass;
			m_mean += m_particles[i]->getPos();
		}
		m_com /= m_mass;
		m_mean /= m_particles.size();
	}
}


QuadTree::QuadTree(){}

void QuadTree::addElements(std::vector<Particle> p_particles) {
	particleList = p_particles;
	indexElements();
	//headNode = new TreeNode(particlePointers);
}

void QuadTree::indexElements() {
	for (int i = 0; i < particleList.size(); ++i) {
		particlePointers.push_back(&particleList.front() + i);
	}
}

void QuadTree::distribute() {

}
 