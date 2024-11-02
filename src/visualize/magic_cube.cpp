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
    bool highlighted;  // New property for highlighting state
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

// Highlight color
const GLfloat highlightColor[] = {1.0f, 1.0f, 1.0f, 0.5f};  // White with 0.5 opacity

// Ray structure for picking
struct Ray {
    float originX, originY, originZ;
    float dirX, dirY, dirZ;
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
    float offset = 2.0f;
    for (int x = 0; x < 5; x++) {
        for (int y = 0; y < 5; y++) {
            for (int z = 0; z < 5; z++) {
                CubeCell cell;
                cell.number = numbers[index++];
                cell.x = (x - 2.0f) * offset;
                cell.y = (y - 2.0f) * offset;
                cell.z = (z - 2.0f) * offset;
                cell.highlighted = false;  // Initialize highlight state
                cells.push_back(cell);
            }
        }
    }
}

// Draw a single number centered in the cube
void drawCenteredNumber(const char* str, float size) {
    float width = 0;
    for (const char* c = str; *c != '\0'; c++) {
        width += glutStrokeWidth(GLUT_STROKE_MONO_ROMAN, *c);
    }
    
    glPushMatrix();
    glTranslatef(-width * 0.5f * 0.003f, -0.05f, size + 0.01f);
    glLineWidth(3.0f);
    
    const int NUM_PASSES = 5;
    for(int i = 0; i < NUM_PASSES; i++) {
        glPushMatrix();
        glTranslatef(i * 0.0001f, i * 0.0001f, 0);
        glScalef(0.003f, 0.003f, 0.003f);
        for (const char* c = str; *c != '\0'; c++) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, *c);
        }
        glPopMatrix();
    }
    
    glLineWidth(1.0f);
    glPopMatrix();
}

// Draw a single sub-cube
void drawSubCube(const CubeCell& cell) {
    float size = 0.45f;
    glPushMatrix();
    glTranslatef(cell.x, cell.y, cell.z);
    
    glDepthMask(GL_FALSE);
    
    // Draw highlight if cell is selected
    if (cell.highlighted) {
        glColor4fv(highlightColor);
        glBegin(GL_QUADS);
        // Front
        glVertex3f(-size * 1.1f, -size * 1.1f, size * 1.1f);
        glVertex3f(size * 1.1f, -size * 1.1f, size * 1.1f);
        glVertex3f(size * 1.1f, size * 1.1f, size * 1.1f);
        glVertex3f(-size * 1.1f, size * 1.1f, size * 1.1f);
        // Back
        glVertex3f(-size * 1.1f, -size * 1.1f, -size * 1.1f);
        glVertex3f(-size * 1.1f, size * 1.1f, -size * 1.1f);
        glVertex3f(size * 1.1f, size * 1.1f, -size * 1.1f);
        glVertex3f(size * 1.1f, -size * 1.1f, -size * 1.1f);
        // Top
        glVertex3f(-size * 1.1f, size * 1.1f, -size * 1.1f);
        glVertex3f(-size * 1.1f, size * 1.1f, size * 1.1f);
        glVertex3f(size * 1.1f, size * 1.1f, size * 1.1f);
        glVertex3f(size * 1.1f, size * 1.1f, -size * 1.1f);
        // Bottom
        glVertex3f(-size * 1.1f, -size * 1.1f, -size * 1.1f);
        glVertex3f(size * 1.1f, -size * 1.1f, -size * 1.1f);
        glVertex3f(size * 1.1f, -size * 1.1f, size * 1.1f);
        glVertex3f(-size * 1.1f, -size * 1.1f, size * 1.1f);
        // Right
        glVertex3f(size * 1.1f, -size * 1.1f, -size * 1.1f);
        glVertex3f(size * 1.1f, size * 1.1f, -size * 1.1f);
        glVertex3f(size * 1.1f, size * 1.1f, size * 1.1f);
        glVertex3f(size * 1.1f, -size * 1.1f, size * 1.1f);
        // Left
        glVertex3f(-size * 1.1f, -size * 1.1f, -size * 1.1f);
        glVertex3f(-size * 1.1f, -size * 1.1f, size * 1.1f);
        glVertex3f(-size * 1.1f, size * 1.1f, size * 1.1f);
        glVertex3f(-size * 1.1f, size * 1.1f, -size * 1.1f);
        glEnd();
    }
    
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
    
    glDepthMask(GL_TRUE);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    std::string numStr = std::to_string(cell.number);
    drawCenteredNumber(numStr.c_str(), size);
    
    glPopMatrix();
}

// Get ray from mouse position
Ray getRayFromMouse(int x, int y) {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble posX1, posY1, posZ1;
    GLdouble posX2, posY2, posZ2;
    
    glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);
    glGetIntegerv(GL_VIEWPORT, viewport);
    
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    
    // Get two points on the ray
    gluUnProject(winX, winY, 0.0f, modelview, projection, viewport, &posX1, &posY1, &posZ1);
    gluUnProject(winX, winY, 1.0f, modelview, projection, viewport, &posX2, &posY2, &posZ2);
    
    Ray ray;
    ray.originX = posX1;
    ray.originY = posY1;
    ray.originZ = posZ1;
    
    // Calculate ray direction
    float length = sqrt((posX2-posX1)*(posX2-posX1) + 
                       (posY2-posY1)*(posY2-posY1) + 
                       (posZ2-posZ1)*(posZ2-posZ1));
    
    ray.dirX = (posX2-posX1)/length;
    ray.dirY = (posY2-posY1)/length;
    ray.dirZ = (posZ2-posZ1)/length;
    
    return ray;
}

// Check if ray intersects with cube
bool rayIntersectsCube(const Ray& ray, const CubeCell& cell, float size) {
    float bounds[2][3] = {
        {cell.x - size, cell.y - size, cell.z - size},
        {cell.x + size, cell.y + size, cell.z + size}
    };
    
    float tmin = (bounds[0][0] - ray.originX) / ray.dirX;
    float tmax = (bounds[1][0] - ray.originX) / ray.dirX;
    
    if (tmin > tmax) std::swap(tmin, tmax);
    
    float tymin = (bounds[0][1] - ray.originY) / ray.dirY;
    float tymax = (bounds[1][1] - ray.originY) / ray.dirY;
    
    if (tymin > tymax) std::swap(tymin, tymax);
    
    if ((tmin > tymax) || (tymin > tmax)) return false;
    
    if (tymin > tmin) tmin = tymin;
    if (tymax < tmax) tmax = tymax;
    
    float tzmin = (bounds[0][2] - ray.originZ) / ray.dirZ;
    float tzmax = (bounds[1][2] - ray.originZ) / ray.dirZ;
    
    if (tzmin > tzmax) std::swap(tzmin, tzmax);
    
    if ((tmin > tzmax) || (tzmin > tmax)) return false;
    
    return true;
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    
    glTranslatef(0.0f, 0.0f, distance);
    glRotatef(rotationX, 1.0f, 0.0f, 0.0f);
    glRotatef(rotationY, 0.0f, 1.0f, 0.0f);
    
    auto cameraPos = std::make_tuple(0.0f, 0.0f, -distance);
    std::vector<std::pair<float, CubeCell>> sortedCells;
    
    for (const auto& cell : cells) {
        float dx = std::get<0>(cameraPos) - cell.x;
        float dy = std::get<1>(cameraPos) - cell.y;
        float dz = std::get<2>(cameraPos) - cell.z;
        float dist = dx*dx + dy*dy + dz*dz;
        sortedCells.push_back({dist, cell});
    }
    
    std::sort(sortedCells.begin(), sortedCells.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });
    
    for (const auto& cell : sortedCells) {
        drawSubCube(cell.second);
    }
    
    glutSwapBuffers();
}

void processClick(int x, int y) {
    Ray ray = getRayFromMouse(x, y);
    float minDist = std::numeric_limits<float>::max();
    int selectedIndex = -1;
    
    // Find the closest intersecting cube
    for (size_t i = 0; i < cells.size(); i++) {
        if (rayIntersectsCube(ray, cells[i], 0.45f)) {
            float dx = cells[i].x - ray.originX;
            float dy = cells[i].y - ray.originY;
            float dz = cells[i].z - ray.originZ;
            float dist = dx*dx + dy*dy + dz*dz;
            
            if (dist < minDist) {
                minDist = dist;
                selectedIndex = i;
            }
        }
    }
    
    // Toggle highlight state of selected cube
    if (selectedIndex >= 0) {
        // Clear all highlights first
        for (auto& cell : cells) {
            cell.highlighted = false;
        }
        cells[selectedIndex].highlighted = true;
        glutPostRedisplay();
    }
}

void mouse(int button, int state, int x, int y) {
    mouseX = x;
    mouseY = y;
    
    if (button == GLUT_LEFT_BUTTON) {
        if (state == GLUT_DOWN) {
            processClick(x, y);
        }
        mouseLeftDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_RIGHT_BUTTON) {
        mouseRightDown = (state == GLUT_DOWN);
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        rotationX = 0.0f;
        rotationY = 0.0f;
        distance = -30.0f;
        glutPostRedisplay();
    }
    else if (button == 3) {
        distance -= mouseZoomSensitivity * 5.0f;
        glutPostRedisplay();
    }
    else if (button == 4) {
        distance += mouseZoomSensitivity * 5.0f;
        glutPostRedisplay();
    }
}

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

// Reshape function
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)w / h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

// Keyboard function for rotation and control
void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': rotationX += 5.0f; break;
        case 's': rotationX -= 5.0f; break;
        case 'a': rotationY -= 5.0f; break;
        case 'd': rotationY += 5.0f; break;
        case 'q': distance += 1.0f; break;
        case 'e': distance -= 1.0f; break;
        case 'r': // Reset view and clear highlights
            rotationX = 0.0f;
            rotationY = 0.0f;
            distance = -30.0f;
            // Clear all highlights
            for (auto& cell : cells) {
                cell.highlighted = false;
            }
            break;
        case 'c': // Clear highlights only
            for (auto& cell : cells) {
                cell.highlighted = false;
            }
            break;
        case 27:  // ESC key
            exit(0);
            break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Magic Cube Visualization with Highlighting");
    
    // Enable necessary OpenGL features
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    
    // Initialize the cube
    initializeCube();
    
    // Register callback functions
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    
    // Print instructions
    printf("Controls:\n");
    printf("Left Mouse: Rotate cube (when dragging)\n");
    printf("Right Mouse: Zoom (when dragging)\n");
    printf("Middle Mouse: Reset view\n");
    printf("Mouse Wheel: Zoom in/out\n");
    printf("Left Click: Select/highlight cube\n");
    printf("W/S: Rotate up/down\n");
    printf("A/D: Rotate left/right\n");
    printf("Q/E: Zoom out/in\n");
    printf("R: Reset view and clear highlights\n");
    printf("C: Clear highlights\n");
    printf("ESC: Exit\n");
    
    glutMainLoop();
    return 0;
}