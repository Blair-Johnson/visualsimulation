#pragma once
#include <Eigen/Dense>
#include <SDL.h>


class Object {
public:
	virtual bool render();
	void setPos(Eigen::Vector2f);
	void setVel(Eigen::Vector2f);
	void setMass(float);
	Eigen::Vector2f getPos();
	Eigen::Vector2f getVel();
	float getMass();
public:
	Eigen::Vector2f m_pos;
	Eigen::Vector2f m_vel;
	float m_m;
};


class Particle: public Object {
public:
	Particle(Eigen::Vector2f, Eigen::Vector2f, float);
private:

};