# Particle-System
# For Arch Linux:
Install sfml and csfml (sudo pacman -S sfml csfml)
Download the files in a folder and just do:
g++ main.cpp Particle.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system && ./sfml-app

# CONTROLS:
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
