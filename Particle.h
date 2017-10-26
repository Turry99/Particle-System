#ifndef PARTICLE_H
#define PARTICLE_H
#include <SFML/Graphics.hpp>

class Particle{
private:
	float x;
	float y;
	sf::Color color;
	float velX;
	float velY;
	bool dead = false;
public:
	Particle(float x, float y, sf::Color color, float velX, float velY);
	float getPosX();
	float getPosY();
	sf::Color getColor();
	void increaseVel(float velocityX, float velocityY);
	void move();
	bool checkIfDead();
	void kill();
	void revertVel();
};


#endif // PARTICLE_H

