#pragma once
#include <vector>
#include "particle.h"


class TreeNode {
public:
	TreeNode(std::vector<Particle*>, float, float, float, float);
public:
	TreeNode* headNode;
	TreeNode* m_subnodes[4];
	std::vector<Particle*> m_particles;
	Eigen::Vector2f m_com;
	float m_mass;
	float xmin, xmax, ymin, ymax;
};

class Quadtree {
public:
	Quadtree();
	void addElements(std::vector<Particle>);
	void update();
private:
	void split();
	TreeNode* headNode;
	std::vector<Particle> particleList;
};
