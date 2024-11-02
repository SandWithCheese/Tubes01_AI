#ifndef VISUALIZE_HPP
#define VISUALIZE_HPP

#include "../cube/magicfive.hpp"
#include <GL/glut.h>
#include <string>
#include <sstream>
#include <iostream>

class Visualize {
private:
    static float angleX;
    static float angleY;
    static float cameraDistance;
    static MagicFive* currentCube;
    static const float CUBE_SIZE;
    static const float SPACING;

    static void drawSmallCube(float x, float y, float z, int number);

    static void init();

    static void display();

    static void reshape(int w, int h);

    static void keyboard(unsigned char key, int x, int y);

public:
    static void initVisualization(int argc, char** argv, MagicFive* cube, const std::string& title = "Magic Five Cube Visualization");
};


#endif
