# work_college_3D_bedroom
Creating a 3D Bedroom with OpenGL in C

# Installation
In wsl2 or Linux system

`sudo apt update`

`sudo apt install libgl1-mesa-dev`

`sudo apt-get install freeglut3-dev`

`sudo apt-get install libsoil-dev`


# Verifing if lib is installed
`sudo find / -name SOIL.h`

`sudo find / -name glut.h`

# Running the project

Browse to project folder and run the follow commands:

`gcc -o bedroom main.c -lGL -lGLU -lglut -I ./include/GL -lSOIL -I/usr/include/SOIL/`

`./bedroom`