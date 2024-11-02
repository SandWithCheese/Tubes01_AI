#include <GL/glut.h>
#include <vector>
#include <random>
#include <algorithm>
#include <string>
#include <cmath>

// Structure to store cube properties
struct CubeCell {
    int number;
    float x, y, z;
};

// Global variables
std::vector<CubeCell> cells;
float rotationX = 0.0f;
float rotationY = 0.0f;
float distance = -30.0f;

// Mouse interaction variables
bool mouseLeftDown = false;
bool mouseRightDown = false;
int mouseX = 0, mouseY = 0;
float mouseRotationSensitivity = 0.5f;
float mouseZoomSensitivity = 0.1f;

// Colors for the cube faces with reduced opacity
const GLfloat colors[][4] = {
    {0.8f, 0.2f, 0.2f, 0.3f},  // Red with 0.3 opacity
    {0.2f, 0.8f, 0.2f, 0.3f},  // Green with 0.3 opacity
    {0.2f, 0.2f, 0.8f, 0.3f},  // Blue with 0.3 opacity
    {0.8f, 0.8f, 0.2f, 0.3f},  // Yellow with 0.3 opacity
    {0.8f, 0.2f, 0.8f, 0.3f},  // Magenta with 0.3 opacity
    {0.2f, 0.8f, 0.8f, 0.3f}   // Cyan with 0.3 opacity
};

// Initialize the cube with random numbers
void initializeCube() {
    std::vector<int> numbers(125);
    for (int i = 0; i < 125; i++) {
        numbers[i] = i + 1;
    }
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(numbers.begin(), numbers.end(), gen);
    
    int index = 0;
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            for (int z = 0; z < 5; z++) {
                CubeCell cell;
                cell.number = numbers[index++];
                cell.x = x - 2.0f;
                cell.y = y - 2.0f;
                cell.z = z - 2.0f;
                cells.push_back(cell);
            }
        }
    }
}

// Draw a single number centered in the cube
void drawCenteredNumber(const char* str, float size) {
    // Calculate text width for centering
    float width = 0;
    for (const char* c = str; *c != '\0'; c++) {
        width += glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, *c);
    }
    
    glPushMatrix();
    // Center the number
    glTranslatef(-width * 0.5f * 0.003f, -0.05f, size + 0.01f);
    
    // Increase line width for thicker numbers
    glLineWidth(3.0f);  // You can adjust this value (1.0 is default, try 2.0-5.0)
    
    // Draw the number multiple times with slight offsets for even thicker appearance
    const int NUM_PASSES = 5;  // Increase this for thicker numbers
    for(int i = 0; i < NUM_PASSES; i++) {
        glPushMatrix();
        // Add tiny offset for each pass
        glTranslatef(i * 0.0001f, i * 0.0001f, 0);
        glScalef(0.003f, 0.003f, 0.003f);
        for (const char* c = str; *c != '\0'; c++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);  // Changed to STROKE_ROMAN for thicker font
        }
        glPopMatrix();
    }
    
    glLineWidth(1.0f);  // Reset line width
    glPopMatrix();
}

// Draw a single sub-cube
void drawSubCube(const CubeCell& cell) {
    float size = 0.45f;
    glPushMatrix();
    glTranslatef(cell.x, cell.y, cell.z);
    
    // Enable depth testing but disable depth writing for transparent faces
    glDepthMask(GL_FALSE);
    
    // Draw cube faces
    glBegin(GL_QUADS);
    // Front
    glColor4fv(colors[0]);
    glVertex3f(-size, -size, size);
    glVertex3f(size, -size, size);
    glVertex3f(size, size, size);
    glVertex3f(-size, size, size);
    
    // Back
    glColor4fv(colors[1]);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, -size, -size);
    
    // Top
    glColor4fv(colors[2]);
    glVertex3f(-size, size, -size);
    glVertex3f(-size, size, size);
    glVertex3f(size, size, size);
    glVertex3f(size, size, -size);
    
    // Bottom
    glColor4fv(colors[3]);
    glVertex3f(-size, -size, -size);
    glVertex3f(size, -size, -size);
    glVertex3f(size, -size, size);
    glVertex3f(-size, -size, size);
    
    // Right
    glColor4fv(colors[4]);
    glVertex3f(size, -size, -size);
    glVertex3f(size, size, -size);
    glVertex3f(size, size, size);
    glVertex3f(size, -size, size);
    
    // Left
    glColor4fv(colors[5]);
    glVertex3f(-size, -size, -size);
    glVertex3f(-size, -size, size);
    glVertex3f(-size, size, size);
    glVertex3f(-size, size, -size);
    glEnd();
    
    // Re-enable depth writing for the number
    glDepthMask(GL_TRUE);
    
    // Draw the number only on the front face
    glColor3f(0.0f, 0.0f, 0.0f);  // Black color for number
    std::string numStr = std::to_string(cell.number);
    drawCenteredNumber(numStr.c_str(), size);
    
    glPopMatrix();
}

// Display function with depth sorting
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, distance);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    
    // Sort cells based on distance from camera for proper transparency
    auto cameraPos = std::make_tuple(0.0f, 0.0f, -distance);
    std::vector<std::pair<float, CubeCell>> sortedCells;
    
    for (const auto& cell : cells) {
        float dx = std::get<0>(cameraPos) - cell.x;
        float dy = std::get<1>(cameraPos) - cell.y;
        float dz = std::get<2>(cameraPos) - cell.z;
        float dist = dx*dx + dy*dy + dz*dz;
        sortedCells.push_back({dist, cell});
    }
    
    // Sort back to front for proper transparency
    std::sort(sortedCells.begin(), sortedCells.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });
    
    // Draw all sub-cubes
    for (const auto& cell : sortedCells) {
        drawSubCube(cell.second);
    }
    
    glutSwapBuffers();
}

// Reshape function
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard function for rotation
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': rotationX += 5.0f; break;
        case 's': rotationX -= 5.0f; break;
        case 'a': rotationY -= 5.0f; break;
        case 'd': rotationY += 5.0f; break;
        case 'q': distance += 1.0f; break;
        case 'e': distance -= 1.0f; break;
        case 'r': // Reset view
            rotationX = 0.0f;
            rotationY = 0.0f;
            distance = -30.0f;
            break;
        case 27:  exit(0); break;  // ESC key
    }
    glutPostRedisplay();
}

// Mouse button callback
void mouse(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
    
    if (button == GLUT_LEFT_BUTTON) {
        mouseLeftDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        mouseRightDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        // Reset view
        rotationX = 0.0f;
        rotationY = 0.0f;
        distance = -30.0f;
        glutPostRedisplay();
    }
    else if (button == 3) { // Mouse wheel up
        distance -= mouseZoomSensitivity * 5.0f;
        glutPostRedisplay();
    }
    else if (button == 4) { // Mouse wheel down
        distance += mouseZoomSensitivity * 5.0f;
        glutPostRedisplay();
    }
}

// Mouse motion callback
void motion(int x, int y) {
    int deltaX = x - mouseX;
    int deltaY = y - mouseY;
    
    if (mouseLeftDown) {
        rotationY += deltaX * mouseRotationSensitivity;
        rotationX += deltaY * mouseRotationSensitivity;
        glutPostRedisplay();
    }
    else if (mouseRightDown) {
        distance += deltaY * mouseZoomSensitivity;
        glutPostRedisplay();
    }
    
    mouseX = x;
    mouseY = y;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Magic Cube Visualization");
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    initializeCube();
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    glutMainLoop();
    return 0;
}