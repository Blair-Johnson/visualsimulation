#pragma once
#include <vector>
#include <cmath>

#include "particle.h"


class TreeNode {
public:
	void assignArgs(std::vector<Particle*>, Eigen::Vector2f, Eigen::Vector2f);
	TreeNode();
	~TreeNode();
	void setSize(int);
	void findCenter();
	void updateIntervals();
	void sortParticles();
	int sortPointer(float, float);
	void pushParticle(Particle*);
	void updateForces(int, int, float, float, float);
	void updateForces(TreeNode*, int, float, float);
	void updateForcesLocal(int, float, float);
	void applyFnet();
	void zeroFnet();
public:
	TreeNode* headNode;
	TreeNode* m_subnodes[4];
	std::vector<Particle*> m_particles;
	std::vector<Particle*> head_reserve;
	std::vector<TreeNode*> leafNodes;
	std::vector<int> treeIndex;
	Eigen::Vector2f m_com;
	Eigen::Vector2f m_mean;
	Eigen::Vector2f m_fnet;
	Eigen::Vector2f x_interval;
	Eigen::Vector2f y_interval;
	float m_mass;
	int size;
};

class QuadTree {
public:
	QuadTree(float, float);
	~QuadTree();
	void addElements(std::vector<Particle>);
	void updateForces(int, int, float, float, float);
private:
	void indexElements();
	void distribute();
	TreeNode* headNode;
	std::vector<Particle> particleList;
	std::vector<Particle*> particlePointers;
	float m_width, m_height;
};
