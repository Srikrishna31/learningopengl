#include<iostream>
#include <GL/glut.h>
#include <gl/GL.h>
#include "ISceneRenderer.h"
#include "TriangleRenderer.h"

#include <memory>
/*
GLUT tutorial from this site:
http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
*/

std::unique_ptr<ISceneRenderer> pRenderer = nullptr;

void renderScene(void)
{
    pRenderer->renderScene();
}

void windowResized(int w, int h)
{
    pRenderer->windowResized(w, h);
}

void processNormalKeys(uint8_t key, int x, int y)
{
    pRenderer->processNormalKeys(key, x, y);
}

void processSpecialKeys(int key, int x, int y)
{
    pRenderer->processSpecialKeys(key, x, y);
}
int main(int argc, char *argv[])
{
    pRenderer = std::make_unique<TriangleRenderer>();

    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D- GLUT Tutorial");
    
    glutDisplayFunc(renderScene); //Called when the Paint message is received from the OS
    glutReshapeFunc(windowResized); //Called when the window is resized;
    glutIdleFunc(renderScene); //Called when the application is idle.
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);

    glutMainLoop();

    return 0;
}

