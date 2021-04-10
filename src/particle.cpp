#include "../include/particle.h"


Color::Color(Uint32 p_r, Uint32 p_g, Uint32 p_b, Uint32 p_a) {
	red = p_r;
	green = p_g;
	blue = p_b;
	alpha = p_a;
}

Color::Color() {
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255;
}

Object::Object() {};

Object::~Object() {};

float Object::getMass() {
	return m_m;
};

Eigen::Vector2f Object::getPos() {
	return m_pos;
};

Eigen::Vector2f Object::getVel() {
	return m_vel;
};

SDL_Renderer* Object::getRenderer() {
	return m_renderer;
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

void Object::setFnet(Eigen::Vector2f p_fnet) {
	m_fnet = p_fnet;
}

Eigen::Vector2f Object::getFnet() {
	return m_fnet;
}

void Object::setRenderer(SDL_Renderer* p_renderer) {
	m_renderer = p_renderer;
}

void Object::setBounds(SDL_Rect p_bbox) {
	m_bbox = p_bbox;
}

SDL_Rect Object::getBounds() {
	return m_bbox;
}

SDL_Rect* Object::getBoundsPtr() {
	return &m_bbox;
}

void Object::setTexture(SDL_Texture* p_texture) {
	m_texture = p_texture;
}

SDL_Texture* Object::getTexture() {
	return m_texture;
}

Particle::Particle(SDL_Renderer* p_renderer, Eigen::Vector2f p_pos, Eigen::Vector2f p_vel, float p_m, int p_rad)
{
	setPos(p_pos);
	setVel(p_vel);
	setMass(p_m);
	setRadius(p_rad);
	setColor(0, 204, 153, 255);

	computeBounds();
	update();
}

void Particle::setRadius(int p_rad) {
	m_rad = p_rad;
}

int Particle::getRadius() {
	return m_rad;
}

void Particle::step(float dt) {
	//physics goes here
	Eigen::Vector2f dv = getFnet()/getMass() * dt;
	setVel(getVel() + dv);
	setPos(getPos() + getVel() * dt);
}

void Particle::update() {
	Uint32 rmask, gmask, bmask, amask;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
	rmask = 0xff000000;
	gmask = 0x00ff0000;
	bmask = 0x0000ff00;
	amask = 0x000000ff;
	Uint32 pixColor = (m_color.red << 24) + (m_color.green << 16) + (m_color.blue << 8) + m_color.alpha;
#else
	rmask = 0x000000ff;
	gmask = 0x0000ff00;
	bmask = 0x00ff0000;
	amask = 0xff000000;
	Uint32 pixColor = (m_color.alpha << 24) + (m_color.blue << 16) + (m_color.green << 8) + m_color.red;
#endif

	// create texture
	SDL_Surface* t_surface = SDL_CreateRGBSurface(0, getBounds().w, getBounds().h, 32, rmask, gmask, bmask, amask);
	setTexture(SDL_CreateTextureFromSurface(getRenderer(), t_surface));
	SDL_FreeSurface(t_surface);

	// allocate pixel buffer
	Uint32* t_pixels = new Uint32[getBounds().w * getBounds().h];

	// clear pixel buffer
	memset(t_pixels, 0, getBounds().w * getBounds().h * sizeof(Uint32));

	// draw a circle
	int cx = getPos()[0] - getBounds().x;
	int cy = getPos()[1] - getBounds().y;
	int r_squared = pow(getRadius(), 2);

	for (int i = 0; i <= getBounds().w / 2; ++i) {
		for (int j = 0; j <= getBounds().h / 2; ++j) {
			int cVal = pow(i - cx, 2) + pow(j - cy, 2) - r_squared;
			if (cVal <= 0) {
				t_pixels[(j * getBounds().w) + i] = pixColor;
				t_pixels[(j * getBounds().w) + ((getBounds().w - 1) - i)] = pixColor;
				t_pixels[(((getBounds().h - 1) - j) * getBounds().w) + i] = pixColor;
				t_pixels[(((getBounds().h - 1) - j) * getBounds().w) + ((getBounds().w - 1) - i)] = pixColor;
			}
		}
	}

	// update the texture with pixel buffer
	SDL_UpdateTexture(getTexture(), NULL, t_pixels, getBounds().w * sizeof(Uint32));

	// delete pixel buffer
	delete[] t_pixels;
}

bool Particle::render() {
	if (getRenderer() != nullptr) {
		// blit texture into the renderer at the appropriate position
		SDL_Rect srcRect; // basically window rect
		srcRect.x = 0;
		srcRect.y = 0;
		srcRect.w = getBounds().w;
		srcRect.h = getBounds().h;

		SDL_RenderCopy(getRenderer(), getTexture(), &srcRect, getBoundsPtr());

		return true;
	}
	else
		return false;
}

void Particle::computeBounds() {
	int left = getPos()[0] - getRadius();
	int top = getPos()[1] - getRadius();
	int width = 2 * getRadius();
	int height = 2 * getRadius();
	SDL_Rect t_bounds = getBounds();
	t_bounds.x = left;
	t_bounds.y = top;
	t_bounds.w = width;
	t_bounds.h = height;
	setBounds(t_bounds);
}

void Particle::setColor(Uint8 p_r, Uint8 p_g, Uint8 p_b, Uint8 p_a) {
	m_color = Color(p_r, p_g, p_b, p_a);
}