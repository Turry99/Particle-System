#include <SFML/Graphics.hpp>
#include "Particle.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <math.h>
#include <string>
/*
For Arch Linux:
Install sfml and csfml (sudo pacman -S sfml csfml)
Download the files in a folder and just do:
g++ main.cpp Particle.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

CONTROLS:
Right click         --> Moves the spawnpoint of the particles.
Left click          --> Puts a bouncing circle. Particles will bounce on them.
Space               --> Clears the bouncing points.
Scrollwheel UP/DOWN --> Increases/Decreases the number of particles spawned per loop.

You can modify the values below in case you want to play with the program.
XVEL          --> How much they move on the X axes (Left/Right)
YVEL          --> How much they move on the Y axes (Up/Down)
BRADIUS       --> The radius of the bouncing circles.
PRADIUS       --> The radius of the particles.
FPS           --> The number of frames per second.
pointOfSpawn  --> No reason to modify them since you can just modify it by clicking.
HEIGHT        --> The size of the window. (It's a square window)
*/


const int HEIGHT = 640;
const float XVEL = 0;
const float YVEL = 1;
const int BRADIUS = 8;
const int PRADIUS = 2;
float pointOfSpawnX = HEIGHT/2;
float pointOfSpawnY = HEIGHT/2;
int numberOfParticles = 15;
const int FPS = 29;

using namespace sf;

float fRand(float fMin, float fMax){
    //Generate a random float number from fMin to fMax
    float f = (float)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

float distance(int posX, int posY, int centerCircleX, int centerCircleY){
    //Calculate the distance between 2 points
    //Formula: sqrt( (Xa - Xb)^2 + (Ya - Yb)^2 )
    return sqrt(pow(posX - centerCircleX, 2) + pow(posY - centerCircleY, 2));
}

int main()
{
    RenderWindow window(VideoMode(HEIGHT, HEIGHT), "SFML works!");
    window.setFramerateLimit(FPS);
    Text text;
    Font font;
    if (!font.loadFromFile("arial.ttf"))
    {
        std::cerr << "We couldn't load the arial font" << std::endl;
    }
    text.setFont(font);
    text.setCharacterSize(12);
    text.setFillColor(Color::White);
    text.setStyle(sf::Text::Bold);
    srand (time(NULL));
    std::vector<Particle> ParticleList;
    std::vector<Vector2i> bouncePoints;



    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            //Increase/Decrease the numberOfParticles.
            if (event.type == sf::Event::MouseWheelScrolled)
            {
                if(event.mouseWheelScroll.delta > 0)
                {
                    numberOfParticles += 1;
                }
                else if(event.mouseWheelScroll.delta < 0)
                {
                    //We just make sure that it can't go below 0
                    if (numberOfParticles < 0) {
                        numberOfParticles = 0;
                    } else {
                        numberOfParticles -= 1;
                    }
                }
            }
        }
        //Move the spawn of the points
        if (Mouse::isButtonPressed(Mouse::Left)){
            Vector2i mousePos = Mouse::getPosition(window);
            pointOfSpawnX = mousePos.x;
            pointOfSpawnY = mousePos.y;
        }
        //Create a pushing circle thingy..
        if (Mouse::isButtonPressed(Mouse::Right)){
            Vector2i mousePos = Mouse::getPosition(window);
            bouncePoints.push_back(mousePos);
        }
        //Clear the bouncing points
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            bouncePoints.clear();
        }

        window.clear(Color::Black);

        //Here we create the particles
        for(int i = 0; i < numberOfParticles; ++i) {
            Color color = Color(rand() % 255, rand() % 255, rand() % 255);
            float xVel = fRand(-3, 3);
            float yVel = fRand(-3, 3);
            ParticleList.push_back(Particle(pointOfSpawnX, pointOfSpawnY, color, xVel, yVel));
        }

        // We delete the particles that are set to dead
        ParticleList.erase(
            std::remove_if(ParticleList.begin(), ParticleList.end(), [](Particle part){ return part.checkIfDead();}),
            ParticleList.end()
            );

        // We draw the particles
        for (std::vector<Particle>::iterator it = ParticleList.begin(); it != ParticleList.end(); it++){

            //If they are out of the screen we set them to dead so we can kill them in the future
            if ((*it).getPosX() > HEIGHT || (*it).getPosX() < 0 || (*it).getPosY() > HEIGHT || (*it).getPosY() < 0){
                (*it).kill();
            }
            //If the circle is inside the bouncy thingy
            for (std::vector<Vector2i>::iterator ci = bouncePoints.begin(); ci != bouncePoints.end(); ci++){
                if (distance( (*it).getPosX(), (*it).getPosY(), (*ci).x, (*ci).y) <= (BRADIUS + PRADIUS) ){
                    (*it).revertVel();
                }
            }
            CircleShape circle;
            (*it).increaseVel(XVEL, YVEL);
            (*it).move();
            circle.setPosition((*it).getPosX(), (*it).getPosY());
            circle.setFillColor( (*it).getColor() );
            circle.setRadius(PRADIUS);
            window.draw(circle);
        }
        //Draw the bouncing points
        for (std::vector<Vector2i>::iterator it = bouncePoints.begin(); it != bouncePoints.end(); it++){
            CircleShape circle;
            circle.setPosition((*it).x, (*it).y);
            circle.setFillColor(Color::White);
            circle.setRadius(BRADIUS);
            window.draw(circle);
        }

        text.setString("Spawn per loop:" + std::to_string(numberOfParticles) + //Show the number of particles spawned per loop
            "\nNumber of particles on screen:" + std::to_string(ParticleList.size())); // How many are on the screen
        
        window.draw(text);
        window.display();
        
    }

    return 0;
}