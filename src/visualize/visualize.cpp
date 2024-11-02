#include "visualize.hpp"


float Visualize::angleX = 30.0f;
float Visualize::angleY = 45.0f;
float Visualize::cameraDistance = 20.0f;
MagicFive* Visualize::currentCube = nullptr;
const float Visualize::CUBE_SIZE = 1.0f;
const float Visualize::SPACING = 1.0f;

void Visualize::drawSmallCube(float x, float y, float z, int number) {
    glPushMatrix();
    glTranslatef(x, y, z);

    // Set border color
    // Light gray color borders
    glColor3f(0.8f, 0.8f, 0.8f);
    glLineWidth(2.0f);

    glBegin(GL_LINES);

    // Front face
    glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
    glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);

    glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);
    glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);

    glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
    glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);

    glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);
    glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);

    // Back face
    glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);

    glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);

    glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);

    glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);

    // Connecting lines
    glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(-CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);

    glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(CUBE_SIZE / 2, -CUBE_SIZE / 2, CUBE_SIZE / 2);

    glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);

    glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, -CUBE_SIZE / 2);
    glVertex3f(-CUBE_SIZE / 2, CUBE_SIZE / 2, CUBE_SIZE / 2);

    glEnd();

    // Draw number inside the cube
    glColor3f(0.0f, 0.0f, 0.0f);
    // Center the text inside the cube
    glRasterPos3f(0.0f, 0.0f, 0.0f);
    std::string numStr = std::to_string(number);
    for (char c : numStr) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }

    glPopMatrix();
}

void Visualize::init() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

void Visualize::display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(0.0f, 0.0f, cameraDistance, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    glRotatef(angleX, 1.0f, 0.0f, 0.0f);
    glRotatef(angleY, 0.0f, 1.0f, 0.0f);

    if (currentCube) {
        auto data = currentCube->getData();
        float startPos = -2 * (CUBE_SIZE + SPACING);

        for (int i = 4; i >= 0; i--) {
            for (int j = 4; j >= 0; j--) {
                for (int k = 4; k >= 0; k--) {
                    float x = startPos + k * (CUBE_SIZE + SPACING);
                    float y = startPos + j * (CUBE_SIZE + SPACING);
                    float z = startPos + i * (CUBE_SIZE + SPACING);

                    drawSmallCube(x, y, z, data[i][j * 5 + k]);
                }
            }
        }
    }

    glutSwapBuffers();
}

void Visualize::reshape(int w, int h) {
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, static_cast<float>(w) / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void Visualize::keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'x': angleX += 5.0f; break;
    case 'X': angleX -= 5.0f; break;
    case 'y': angleY += 5.0f; break;
    case 'Y': angleY -= 5.0f; break;
    case '+': cameraDistance -= 1.0f; break;
    case '=': cameraDistance -= 1.0f; break;
    case '-': cameraDistance += 1.0f; break;
    case '_': cameraDistance += 1.0f; break;
    case 27: exit(0); break;
    }
    glutPostRedisplay();
}

void Visualize::initVisualization(int argc, char** argv, MagicFive* cube, const std::string& title) {
    if (!cube) {
        std::cerr << "Error: Cube pointer is null!" << std::endl;
        return;
    }

    currentCube = cube;
    angleX = 30.0f;
    angleY = 45.0f;
    cameraDistance = 20.0f;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 800);
    glutCreateWindow(title.c_str());

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    glutMainLoop();
}
