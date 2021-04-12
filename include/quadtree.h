#pragma once
#include <vector>
#include "particle.h"


class TreeNode {
public:
	TreeNode(std::vector<Particle*>, std::tuple<float,float>, std::tuple<float,float>);
	~TreeNode();
	void findCenter();
public:
	TreeNode* headNode;
	TreeNode* m_subnodes[4];
	std::vector<Particle*> m_particles;
	Eigen::Vector2f m_com;
	Eigen::Vector2f m_mean;
	float m_mass;
	std::tuple<float, float> x_interval, y_interval;
};

class QuadTree {
public:
	QuadTree();
	~QuadTree();
	void addElements(std::vector<Particle>);
	void updateForces();
private:
	void indexElements();
	void distribute();
	TreeNode* headNode;
	std::vector<Particle> particleList;
	std::vector<Particle*> particlePointers;
};
