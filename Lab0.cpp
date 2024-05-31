#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath> 
#include <cstdlib>
#include <cstdio>
#include <vector>
using namespace std;

int window;
vector<int> x_arr;
vector<int> y_arr;

vector<int> x_point_arr;
vector<int> y_point_arr;
vector<float> Red_arr;
vector<float> Green_arr;
vector<float> Blue_arr;

void myMouseMoving(int x, int y);
void mousePoint(int bin, int state, int x, int y);
void mouseLine(int bin, int state, int x, int y);
void mouseCircle(int bin, int state, int x, int y);
void mousePolygon(int bin, int state, int x, int y);
void mouseCleanCallback();
void myKeyBoard(unsigned char key, int x, int y);
float random_func();
void randomRGB();
void savePixel(int x_point, int y_point, float SaveRed, float SaveGreen, float SaveBlue);
void displayPoint();
void drawPoint();
void displayLine();
void drawLine();
void displayCircle();
void drawCircle();
void displayPolygon();
void drawPolygon();
void drawALine(int x_start, int x_end, int y_start, int y_end, float Red, float Green, float Blue);
void drawACircle(int x_center, int y_center, int x_radius, int y_radius, float Red, float Green, float Blue);
void drawOctant(int xc_, int yc_, int x, int y, float R, float G, float B);

int Point_mouse_state = 0, Line_mouse_state = 0, Circle_mouse_state = 0, Polygon_mouse_state = 0;
int x_start = 0, x_end = 0, y_start = 0, y_end = 0;
int x_center = 0, y_center = 0, x_radius = 0, y_radius = 0;
int x_init = 0, y_init = 0;
float Red, Green, Blue;
bool Clean = false;
int i;

void myMouseMoving(int x, int y)
{
    if (Point_mouse_state == 1){
        x_arr.push_back(x);
        y_arr.push_back(800 - y);
        savePixel(x, 800 - y, Red, Green, Blue);
        glutPostRedisplay();
    }
}

void mousePoint(int bin, int state, int x, int y) {
    if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        mouseCleanCallback();
        randomRGB();
        Point_mouse_state = 1;
    }
    else if (bin == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        Point_mouse_state = 0;
        x_arr.clear();
        y_arr.clear();
    } 
}

void mouseLine(int bin, int state, int x, int y) {
    if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Line_mouse_state == 0) {
        mouseCleanCallback();
        randomRGB();
        x_start = x;
        y_start = 800 - y;
        Line_mouse_state = 1;
    }
    else if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Line_mouse_state == 1) {
        x_end = x;
        y_end = 800 - y;
        glutPostRedisplay();
        Line_mouse_state = 2;
    }
}

void mouseCircle(int bin, int state, int x, int y) {
    if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Circle_mouse_state == 0) {
        mouseCleanCallback();
        randomRGB();
        x_center = x;
        y_center = 800 - y;
        Circle_mouse_state = 1;
    }
    else if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Circle_mouse_state == 1) {
        x_radius = x;
        y_radius = 800 - y;
        glutPostRedisplay();
        Circle_mouse_state = 2;
    }
}

void mousePolygon(int bin, int state, int x, int y) {
    if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Polygon_mouse_state == 0) {
        mouseCleanCallback();
        randomRGB();
        x_init = x;
        y_init = 800 - y;
        x_start = x;
        y_start = 800 - y;
        x_end = x;
        y_end = 800 - y;
        Polygon_mouse_state = 1;
    }
    else if (bin == GLUT_LEFT_BUTTON && state == GLUT_DOWN && Polygon_mouse_state >= 1) {
        x_start = x_end;
        y_start = y_end;
        x_end = x;
        y_end = 800 - y;
        glutPostRedisplay();
        Polygon_mouse_state = Polygon_mouse_state + 1;
    }
    if (bin == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && Polygon_mouse_state > 1) {
        x_start = x_end;
        y_start = y_end;
        x_end = x_init;
        y_end = y_init;
        glutPostRedisplay();
    }
    else if (bin == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && Polygon_mouse_state == 1) {
        Polygon_mouse_state = 0;
    }
}

void mouseCleanCallback() {
    if (Clean == true) {
        x_point_arr.clear();
        y_point_arr.clear();
        Red_arr.clear();
        Green_arr.clear();
        Blue_arr.clear();
        Clean = false;
    }
}

void myKeyBoard(unsigned char key, int x, int y) {
    switch (key) {
    case 'd': {
        // draw point
        Point_mouse_state = 0;
        glutDisplayFunc(displayPoint);
        glutMouseFunc(mousePoint);
        glutMotionFunc(myMouseMoving);
        break;
    }
    case 'l': {
        // draw line
        Line_mouse_state = 0;
        glutDisplayFunc(displayLine);
        glutMouseFunc(mouseLine);
        glutMotionFunc(NULL);    // NULL的目的是把myMouseMoving這個callback function換掉
        break;
    }
    case 'o': {
        // draw circle
        Circle_mouse_state = 0;
        glutDisplayFunc(displayCircle);
        glutMouseFunc(mouseCircle);
        glutMotionFunc(NULL);
        break;
    }
    case 'p': {
        // draw polygon
        Polygon_mouse_state = 0;
        glutDisplayFunc(displayPolygon);
        glutMouseFunc(mousePolygon);
        glutMotionFunc(NULL);  
        break;
    }
    case 'c': {
        // clean the screen
        glClear(GL_COLOR_BUFFER_BIT);
        glutSwapBuffers();
        Point_mouse_state = 0;
        Line_mouse_state = 0;
        Circle_mouse_state = 0;
        Polygon_mouse_state = 0;
        Clean = true;
        break;
    }
    case 'r': {
        // undo the graphic on the screen
        glutSwapBuffers();
        glutPostRedisplay();
        glPointSize(1);
        glBegin(GL_POINTS);
        for (int i = 0; i < x_point_arr.size(); i++)
        {
            glColor3f(Red_arr[i], Green_arr[i], Blue_arr[i]);
            glVertex2i(x_point_arr[i], y_point_arr[i]);
        }
        glEnd();
        Clean = false;
        break;
    }
    case 'q': {
        exit(0);
    }

    }
}

float random_func() {
    float randomValue = (float)rand() / RAND_MAX;
    return randomValue;
}

void randomRGB() {
    Red = random_func();
    Green = random_func();
    Blue = random_func();
    glColor3f(Red, Green, Blue);
}

void savePixel(int x_point, int y_point, float SaveRed, float SaveGreen, float SaveBlue) {
    x_point_arr.push_back(x_point);
    y_point_arr.push_back(y_point);
    Red_arr.push_back(SaveRed);
    Green_arr.push_back(SaveGreen);
    Blue_arr.push_back(SaveBlue);
};

void displayPoint() {
    drawPoint();
    glutSwapBuffers();
}

void drawPoint() {
    glPointSize(1);
    glBegin(GL_POINTS);
    for (int i = 0; i < x_arr.size(); i++) {
        glVertex2i(x_arr[i], y_arr[i]);
    }
    glEnd();
}

void displayLine() {
    drawLine();
    glutSwapBuffers();
}

void drawLine() {
    glPointSize(1);
    glBegin(GL_POINTS);
    if (Line_mouse_state == 2) {
        drawALine(x_start, x_end, y_start, y_end, Red, Green, Blue);
        Line_mouse_state = 0;
    }
    glEnd();
}

void displayCircle() {
    drawCircle();
    glutSwapBuffers();
}

void drawCircle() {
    glPointSize(1);
    glBegin(GL_POINTS);
    if (Circle_mouse_state == 2) {
        drawACircle(x_center, y_center, x_radius, y_radius, Red, Green, Blue);
        Circle_mouse_state = 0;
    }
    glEnd();
}

void displayPolygon() {
    drawPolygon();
    glutSwapBuffers();
}

void drawPolygon() {
    glPointSize(1);
    glBegin(GL_POINTS);
    if (Polygon_mouse_state >= 2) {
        drawALine(x_start, x_end, y_start, y_end, Red, Green, Blue);
        if (x_end == x_init && y_end == y_init) {
            Polygon_mouse_state = 0;
        }
    }
    glEnd();
}

void drawALine(int x_start, int x_end, int y_start, int y_end, float R, float G, float B) {
    int dx = x_end - x_start;
    int dy = y_end - y_start;
    if (abs(dy) < abs(dx)) {
        if (x_end > x_start) {
            for (i = x_start; i <= x_end; i++) {
                glVertex2i(i, round(y_start + dy * (i - x_start) / dx));
                savePixel(i, (int)round(y_start + dy * (i - x_start) / dx), Red, Green, Blue);
            }
        }
        else {
            for (i = x_start; i >= x_end; i--) {
                glVertex2i(i, round(y_start + dy * (i - x_start) / dx));
                savePixel(i, (int)round(y_start + dy * (i - x_start) / dx), Red, Green, Blue);
            }
        }
    }
    else if (abs(dx) == 0 && abs(dy) == 0) {
        glVertex2i(x_start, y_start);
        savePixel(x_start, y_start, Red, Green, Blue);
    }
    else if (abs(dx) <= abs(dy)) {
        if (y_end > y_start) {
            for (i = y_start; i <= y_end; i++) {
                glVertex2i(round(x_start + dx * (i - y_start) / dy), i);
                savePixel((int)round(x_start + dx * (i - y_start) / dy), i, Red, Green, Blue);
            }
        }
        else {
            for (i = y_start; i >= y_end; i--) {
                glVertex2i(round(x_start + dx * (i - y_start) / dy), i);
                savePixel((int)round(x_start + dx * (i - y_start) / dy), i, Red, Green, Blue);
            }
        }
    }
}

void drawACircle(int x_center, int y_center, int x_radius, int y_radius, float Red, float Green, float Blue){
    int center = 0;
    int radius = round(sqrt((x_radius - x_center) * (x_radius - x_center) + (y_radius - y_center) * (y_radius - y_center)));
    int para = 3 - 2 * radius;
    drawOctant(x_center, y_center, center, radius, Red, Green, Blue);
    while (radius >= center) {
        center++;
        if (para > 0) {
            radius--;
            para = para + 4 * (center - radius) + 10;
        }
        else {
            para = para + 4 * center + 6;
        }
        drawOctant(x_center, y_center, center, radius, Red, Green, Blue);
    }
}

void drawOctant(int xc_, int yc_, int x, int y, float R, float G, float B) {

    glVertex2i(xc_ + x, yc_ + y);
    glVertex2i(xc_ - x, yc_ + y);
    glVertex2i(xc_ + x, yc_ - y);
    glVertex2i(xc_ - x, yc_ - y);
    glVertex2i(xc_ + y, yc_ + x);
    glVertex2i(xc_ - y, yc_ + x);
    glVertex2i(xc_ + y, yc_ - x);
    glVertex2i(xc_ - y, yc_ - x);
    savePixel(xc_ + x, yc_ + y, Red, Green, Blue);
    savePixel(xc_ - x, yc_ + y, Red, Green, Blue);
    savePixel(xc_ + x, yc_ - y, Red, Green, Blue);
    savePixel(xc_ - x, yc_ - y, Red, Green, Blue);
    savePixel(xc_ + y, yc_ + x, Red, Green, Blue);
    savePixel(xc_ - y, yc_ + x, Red, Green, Blue);
    savePixel(xc_ + y, yc_ - x, Red, Green, Blue);
    savePixel(xc_ - y, yc_ - x, Red, Green, Blue);
}

int main(int argc, char* argv[]) {

    glutInit(&argc, argv);
    fgetc(stdin);
    glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    gluOrtho2D(0, 800, 0, 800); 

    window = glutCreateWindow("Your First GLUT  Window!");
    glutDisplayFunc(displayPoint);
    glutMouseFunc(mousePoint);
    glutMotionFunc(myMouseMoving);
    glutKeyboardFunc(myKeyBoard);
    gluOrtho2D(0, 800, 0, 800);
    glutMainLoop();
    return 0;
}


