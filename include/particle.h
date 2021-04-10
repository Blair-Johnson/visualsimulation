#pragma once
#include <Eigen/Dense>
#include <SDL.h>
#include <cmath>


struct Color {
public:
	Color();
	Color(Uint32, Uint32, Uint32, Uint32);
	Uint32 red;
	Uint32 green;
	Uint32 blue;
	Uint32 alpha;
};

class Object {
public:
	Object();
	virtual ~Object();
	void setRenderer(SDL_Renderer*);
	SDL_Renderer* getRenderer();
	void setBounds(SDL_Rect);
	SDL_Rect getBounds();
	SDL_Rect* getBoundsPtr();
	void setTexture(SDL_Texture*);
	SDL_Texture* getTexture();
	virtual bool render() {
		return false;
	};

public:
	void setPos(Eigen::Vector2f);
	void setVel(Eigen::Vector2f);
	void setMass(float);
	void setFnet(Eigen::Vector2f);
	void zeroFnet();
	virtual void updateFnet();
	Eigen::Vector2f getFnet();
	Eigen::Vector2f getPos();
	Eigen::Vector2f getVel();
	float getMass();

private:
	SDL_Renderer* m_renderer;
	SDL_Texture* m_texture;
	SDL_Rect m_bbox;

	Eigen::Vector2f m_pos;
	Eigen::Vector2f m_vel;
	Eigen::Vector2f m_fnet;
	float m_m;
};


class Particle: public Object {
public:
	Particle(SDL_Renderer*, Eigen::Vector2f, Eigen::Vector2f, float, int);
	void setColor(Uint8, Uint8, Uint8, Uint8);
	bool render();
	void setRadius(int);
	int getRadius();
	void step(float);
	void updateFnet(Particle*);
	void checkLimits(int, int);

private:
	void computeBounds();
	void update();
	int m_rad;
	Color m_color;

};