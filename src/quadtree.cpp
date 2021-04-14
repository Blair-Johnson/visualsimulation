#include "../include/quadtree.h"

void TreeNode::assignArgs(std::vector<Particle*> p_particles, Eigen::Vector2f px_interval, Eigen::Vector2f py_interval)
{
	m_particles = p_particles;
	x_interval = px_interval;
	y_interval = py_interval;
	m_mass = 0;
	findCenter();
}

TreeNode::TreeNode() {};

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
	m_subnodes[0]->x_interval = {x_interval[0], m_mean[0]};
	m_subnodes[0]->y_interval = { y_interval[0], m_mean[1] };
	m_subnodes[1]->x_interval = { m_mean[0], x_interval[1] };
	m_subnodes[1]->y_interval = { y_interval[0], m_mean[1] };
	m_subnodes[2]->x_interval = { x_interval[0], m_mean[0] };
	m_subnodes[2]->y_interval = { m_mean[1], y_interval[1] };
	m_subnodes[3]->x_interval = { m_mean[0], x_interval[1] };
	m_subnodes[3]->y_interval = { m_mean[1], y_interval[1] };
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
}

void QuadTree::indexElements() {
	for (int i = 0; i < particleList.size(); ++i) {
		particlePointers.push_back(&particleList.front() + i);
	}
}

void QuadTree::distribute() {
	headNode->findCenter();
	headNode->updateIntervals();
}
 