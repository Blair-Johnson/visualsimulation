#pragma once
#include <vector>
#include "particle.h"


class TreeNode {
public:
	void assignArgs(std::vector<Particle*>, Eigen::Vector2f, Eigen::Vector2f);
	TreeNode();
	~TreeNode();
	void findCenter();
	void updateIntervals();
public:
	TreeNode* headNode;
	TreeNode* m_subnodes[4];
	std::vector<Particle*> m_particles;
	Eigen::Vector2f m_com;
	Eigen::Vector2f m_mean;
	float m_mass;
	Eigen::Vector2f x_interval;
	Eigen::Vector2f y_interval;
};

class QuadTree {
public:
	QuadTree(float, float);
	~QuadTree();
	void addElements(std::vector<Particle>);
	void updateForces();
private:
	void indexElements();
	void distribute();
	TreeNode* headNode;
	std::vector<Particle> particleList;
	std::vector<Particle*> particlePointers;
	float m_width, m_height;
};
