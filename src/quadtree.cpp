#include "../include/quadtree.h"

void TreeNode::assignArgsHead(std::vector<Particle*> p_particles, Eigen::Vector2f px_interval, Eigen::Vector2f py_interval)
{
	m_particles = p_particles;
	headNode = this;
	head_reserve = p_particles;
	x_interval = px_interval;
	y_interval = py_interval;
	m_mass = 0;
	findCenter();

}

TreeNode::TreeNode() {
	TreeNode* m_subnodes[4] = {NULL, NULL, NULL, NULL};
	TreeNode* headNode = NULL;
	std::vector<Particle*> m_particles;
	std::vector<Particle*> head_reserve;
	std::vector<TreeNode*> leafNodes;
	Eigen::Vector2f m_com;
	Eigen::Vector2f m_mean;
	Eigen::Vector2f x_interval;
	Eigen::Vector2f y_interval;
	float m_mass;
	int size;

}

TreeNode::~TreeNode() {
	//Need to correctly delete all dynamically allocated subnodes;
	for (int i = 0; i < 4; ++i) {
		if (m_subnodes[i] != NULL) {
			delete m_subnodes[i];
		}
	}
}

void TreeNode::reset() {
	if (headNode == this) {
		for (int i = 0; i < 4; ++i) {
			if (m_subnodes[i] != NULL) {
				delete m_subnodes[i];
			}
		}
		leafNodes.clear();
		m_particles = head_reserve;
	}
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
		//At some point my particles are becoming junk
		m_com /= m_mass;
		m_mean /= m_particles.size();
	}

}

void TreeNode::updateIntervals() {
	//non-center coordinates may or may not be irrelevant
	if (m_subnodes[0] != NULL) {
		m_subnodes[0]->x_interval = { x_interval[0], m_mean[0] };
		m_subnodes[0]->y_interval = { y_interval[0], m_mean[1] };
	}
	if (m_subnodes[1] != NULL) {
		m_subnodes[1]->x_interval = { m_mean[0], x_interval[1] };
		m_subnodes[1]->y_interval = { y_interval[0], m_mean[1] };
	}
	if (m_subnodes[2] != NULL) {
		m_subnodes[2]->x_interval = { x_interval[0], m_mean[0] };
		m_subnodes[2]->y_interval = { m_mean[1], y_interval[1] };
	}
	if (m_subnodes[3] != NULL) {
		m_subnodes[3]->x_interval = { m_mean[0], x_interval[1] };
		m_subnodes[3]->y_interval = { m_mean[1], y_interval[1] };
	}
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
	if (headNode == this) {
		head_reserve.push_back(p_particle);
	}
}

void TreeNode::sortParticles() {
	if (m_particles.size() > size) {
		// if > sqrt(total), distribute into subnodes
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
				m_subnodes[index]->headNode = headNode;
				m_subnodes[index]->setSize(size);
				m_subnodes[index]->pushParticle(t_particle);
			}
			m_particles.pop_back();
		}
		updateIntervals();
		for (int i = 0; i < 4; ++i) {
			if (m_subnodes[i] != NULL) {
				m_subnodes[i]->findCenter();
				//m_subnodes[i]->updateIntervals();
				m_subnodes[i]->sortParticles();
			}
		}
	}
	else {
		//is a leaf node
		headNode->leafNodes.push_back(this);
	}
}

void TreeNode::applyFnet() {
	if (m_particles.size() > 0) {
		for (int i = 0; i < m_particles.size(); ++i) {
			m_particles[i]->setFnet(m_particles[i]->getFnet() + m_fnet);
		}
	}
}

void TreeNode::zeroFnet() {
	//for (int i = 0; i < m_particles.size(); ++i) {
	//	m_particles[i]->zeroFnet();
	//}
	m_fnet.setZero();
}

void TreeNode::updateForces(int p_atr, float p_interaction_coeff, float p_min_interaction_dist) {
	if (headNode == this) {
		for (int i = 0; i < leafNodes.size(); ++i) {
			leafNodes[i]->zeroFnet();
		}
		for (int i = 0; i < leafNodes.size(); ++i) {
			for (int j = i + 1; j < leafNodes.size(); ++j) {
				leafNodes[i]->updateForces(leafNodes[j], p_atr, p_interaction_coeff, p_min_interaction_dist);
			}
			leafNodes[i]->updateForcesLocal(p_atr, p_interaction_coeff, p_min_interaction_dist);
			leafNodes[i]->applyFnet();
		}
	}
}

void TreeNode::updateForces(TreeNode* p_leaf, int p_atr, float p_interaction_coeff, float p_min_interaction_dist) {
	Eigen::Vector2f r_vec = p_leaf->m_com - m_com;
	float r_mag = r_vec.squaredNorm();
	r_vec /= r_vec.norm();
	float rad = pow(pow((x_interval[1] - x_interval[0]) / 4, 2) + pow((y_interval[1] - y_interval[0]) / 4, 2), 0.5);
	r_vec = p_atr * p_interaction_coeff * (m_mass * p_leaf->m_mass) / (r_mag + p_min_interaction_dist*rad) * r_vec;
	p_leaf->m_fnet -= r_vec;
	m_fnet += r_vec;
}

void TreeNode::updateForcesLocal(int p_atr, float p_interaction_coeff, float p_min_interaction_dist) {
	for (int i = 0; i < m_particles.size(); ++i) {
		for (int j = i + 1; j < m_particles.size(); ++j) {
			m_particles[i]->updateFnet(m_particles[j], p_atr, p_interaction_coeff, p_min_interaction_dist);
		}
	}
}

QuadTree::QuadTree(float p_width, float p_height)
	:m_width(p_width), m_height(p_height)
{
	headNode = new TreeNode;
	headNode->headNode = headNode;
	Eigen::Vector2f x_interval(0, m_width);
	Eigen::Vector2f y_interval(0, m_height);
	headNode->x_interval = x_interval;
	headNode->y_interval = y_interval;
}

void QuadTree::addElements(std::vector<Particle*> p_particles) {
	particlePointers = p_particles;
	headNode->assignArgsHead(particlePointers, x_interval, y_interval);
	headNode->setSize(int(pow(particlePointers.size(),0.5)));
}

void QuadTree::distribute() {



	//headNode->reset();
	//headNode->findCenter();

	headNode->updateIntervals();

	headNode->sortParticles();

	
}

void QuadTree::updateForces(int atr, float interaction_coeff, float min_interaction_dist) {
	headNode->updateForces(atr, interaction_coeff, min_interaction_dist);
}

QuadTree::~QuadTree() {
	delete headNode;
}

void QuadTree::pushElement(Particle *p_particle, Particle p_particleObj) {
	particlePointers.push_back(p_particle);
	particleList.push_back(p_particleObj);
}

void QuadTree::initHeadNode() {
	headNode->assignArgsHead(particlePointers, x_interval, y_interval);
	headNode->setSize(int(pow(particlePointers.size(), 0.5)));
}
 
QuadTree::QuadTree() {}