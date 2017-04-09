#include<iostream>
#include <gl/glut.h>
#include <gl/GL.h>
/*
GLUT tutorial from this site:
http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
*/

void renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glutSwapBuffers();
}

int main(int argc, char *argv[])
{
    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D- GLUT Tutorial");
    
    glutDisplayFunc(renderScene);

    glutMainLoop();

    return 0;
}

