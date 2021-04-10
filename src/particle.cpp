#include "../include/particle.h"


Object::Object() {};

float Object::getMass() {
	return m_m;
};

Eigen::Vector2f Object::getPos() {
	return m_pos;
};

Eigen::Vector2f Object::getVel() {
	return m_vel;
};

void Object::setMass(float p_m) {
	m_m = p_m;
};

void Object::setPos(Eigen::Vector2f p_pos) {
	m_pos = p_pos;
};

void Object::setVel(Eigen::Vector2f p_vel) {
	m_vel = p_vel;
};

Particle::Particle(Eigen::Vector2f p_pos, Eigen::Vector2f p_vel, float p_m) 
{
	setPos(p_pos);
	setVel(p_vel);
	setMass(p_m);
}

