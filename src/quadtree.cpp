#include "../include/quadtree.h"

void TreeNode::assignArgs(std::vector<Particle*> p_particles, Eigen::Vector2f px_interval, Eigen::Vector2f py_interval)
{
	m_particles = p_particles;
	x_interval = px_interval;
	y_interval = py_interval;
	m_mass = 0;
	findCenter();
}

TreeNode::TreeNode() {
	TreeNode* m_subnodes[4] = {};
};

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

void TreeNode::updateIntervals() {
	//non-center coordinates may or may not be irrelevant
	m_subnodes[0]->x_interval = {x_interval[0], m_mean[0]};
	m_subnodes[0]->y_interval = { y_interval[0], m_mean[1] };
	m_subnodes[1]->x_interval = { m_mean[0], x_interval[1] };
	m_subnodes[1]->y_interval = { y_interval[0], m_mean[1] };
	m_subnodes[2]->x_interval = { x_interval[0], m_mean[0] };
	m_subnodes[2]->y_interval = { m_mean[1], y_interval[1] };
	m_subnodes[3]->x_interval = { m_mean[0], x_interval[1] };
	m_subnodes[3]->y_interval = { m_mean[1], y_interval[1] };
}

int TreeNode::sortPointer(float x, float y) {
	if ((x >= x_interval[0]) && (x < m_mean[0])) {
		if ((y >= y_interval[0]) && (y < m_mean[1])) {
			return 0;
		}
		else if ((y >= m_mean[1]) && (y < y_interval[1])) {
			return 2;
		}
	}
	else if ((x >= m_mean[0]) && (x < x_interval[1])) {
		if ((y >= y_interval[0]) && (y < m_mean[1])) {
			return 1;
		}
		else if ((y >= m_mean[1]) && (y < y_interval[1])) {
			return 3;
		}
	}
}

void TreeNode::setSize(int p_size) {
	size = p_size;
}

void TreeNode::pushParticle(Particle* p_particle) {
	m_particles.push_back(p_particle);
}

void TreeNode::sortParticles() {
	if (m_particles.size() > size) {
		int index;
		Particle* t_particle;
		Eigen::Vector2f t_pos;
		for (int i = 0; i < m_particles.size(); ++i) {
			t_particle = m_particles.back();
			t_pos = t_particle->getPos();
			index = sortPointer(t_pos[0], t_pos[1]);
			if (m_subnodes[index] != NULL) {
				m_subnodes[index]->pushParticle(t_particle);
			}
			else {
				m_subnodes[index] = new TreeNode;
				m_subnodes[index]->setSize(size);
				m_subnodes[index]->pushParticle(t_particle);
			}
			m_particles.pop_back();
		}
	}
	for (int i = 0; i < 4; ++i) {
		if (m_subnodes[i] != NULL) {
			m_subnodes[i]->findCenter();
			m_subnodes[i]->updateIntervals();
			m_subnodes[i]->sortParticles();
		}
	}
}

QuadTree::QuadTree(float p_width, float p_height)
	:m_width(p_width), m_height(p_height)
{}

void QuadTree::addElements(std::vector<Particle> p_particles) {
	particleList = p_particles;
	Eigen::Vector2f x_interval(0, m_width);
	Eigen::Vector2f y_interval(0, m_height);
	indexElements();
	headNode = new TreeNode;
	headNode->assignArgs(particlePointers, x_interval, y_interval);
	headNode->setSize(int(pow(p_particles.size(),0.5)));
}

void QuadTree::indexElements() {
	for (int i = 0; i < particleList.size(); ++i) {
		particlePointers.push_back(&particleList.front() + i);
	}
}

void QuadTree::distribute() {
	headNode->findCenter();
	headNode->updateIntervals();
	headNode->sortParticles();
}
 