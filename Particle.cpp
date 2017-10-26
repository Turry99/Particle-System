#include "Particle.h"
#include <SFML/Graphics.hpp>


Particle::Particle(float _x, float _y, sf::Color _color, float _velX, float _velY) {
	x = _x;
	y = _y;
	color = _color;
	velX = _velX;
	velY = _velY;
	dead = false;
}


float Particle::getPosX(){
	return x;
}

float Particle::getPosY(){
	return y;
}

sf::Color Particle::getColor(){
	return color;
}

void Particle::increaseVel(float velocityX, float velocityY){
	velX += velocityX;
	velY += velocityY;
}

void Particle::move(){
	x += velX;
	y += velY;
}

void Particle::kill(){
	dead = true;
}

bool Particle::checkIfDead(){
	return dead;
}

void Particle::revertVel(){
	velX = -velX;
	velY = -velY;
}