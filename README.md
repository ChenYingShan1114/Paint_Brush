# 3D Computer Graphics assignment ([Lab1](https://hackmd.io/TpltIfbET3O9X64BYrsNKQ?view))
### Work requirements:
1. Write the functions of drawing point (d), Line (l), circle (o), polygon (p), clear (c), restore (r) and end program (q).
1. Use the **keyboard** to switch between various functions.
1. Use the **mouse** to click the coordinates assigned to the graph.
1. Only use the function of drawing **points** in OpenGL.

## Environment
`Linux distribution`: `Ubuntu 22.04`<br>
About how to build the enviroment on linux: [here](https://hackmd.io/3xPNjv6kRh2Ml6Ll7Nlw4A).
## Operating instructions
* ### Draw Points (d):
    Start drawing graphic when you press the left mouse button.<br> 
    Stop drawing graphic when you release the left mouse button.  
* ### Draw Lines (l):
    First click to assign the starting point.<br>
    Second click to assign the ending point.
* ### Draw Circles (o):
    First click to assign the center of circle.<br>
    Second click to assign the radius of circle.
* ### Draw Polygons (p):
    Left click to assign the coordinates of polygon.<br>
    Right click to close the polygon.
* ### Clear (c):
    Press keyboard button c to clean the screen.
* ### Undo (r):
    Press keyboard button r to undo the clean action.<br>
    **This feature only works after cleaning the screen.**
* ### Quit (q):
    Press keyboard button q to quit the window.

* ### Bonus function:
    Each graph automatically has a different color.

## Libraries
* ### C++
```cpp
#include <GL/glut.h>
#include <GL/gl.h>
#include <cmath> 
#include <cstdlib>
#include <cstdio>
#include <vector>
```

* ### freeGLUT
```cpp
glutInit(int *&argcp, char **argv);
glutInitWindowSize(int width, int height);
glutInitWindowPosition(int x, int y);
glutInitDisplayMode(unsigned int mode);
glutPostRedisplay(void);
glutSwapBuffers(void);
glutMainLoop();
glutCreateWindow(char *name);
glutDisplayFunc(void (*func)(void));
glutKeyboardFunc(void (*func)(unsigned char key, int x, int y));
glutMouseFunc(void (*func)(int button, int state, int x, int y));
glutMotionFunc(void (*func)(int x, int y));
```
```
gluOrtho2D(GLdouble left, GLdouble right, GLdouble top, GLdouble bottom); 
glClear(GLbitfield mask);
glPointSize(GLfloat size);
glColor3f(GLfloat red, GLfloat green, GLfloat blue);
glBegin(GLenum mode);
glVertex2i(GLint x, GLint y);
glEnd(void);
```
