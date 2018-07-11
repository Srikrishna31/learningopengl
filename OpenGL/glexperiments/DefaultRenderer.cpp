#include <cstdint>
#include "DefaultRenderer.h"
#include "GL/glut.h"

void DefaultRenderer::renderScene(void)
{

}

void DefaultRenderer::windowResized(int w, int h)
{
    //Prevent divide by 0 when window is too short
    if (h == 0)
        h = 1;

    auto ratio = 1.0f*w / h;

    glViewport(0, 0, w, h);

    setPerspective(w, h, ratio);
}

void DefaultRenderer::setPerspective(int w, int h, float aspectRatio)
{
    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluPerspective(45, aspectRatio, 1, 1000);

    glMatrixMode(GL_MODELVIEW);

}

void DefaultRenderer::processNormalKeys(uint8_t key, int x, int y)
{

}

void DefaultRenderer::processSpecialKeys(int key, int x, int y)
{

}

void DefaultRenderer::processReleaseKey(int key, int x, int y)
{

}

void DefaultRenderer::processMouseButton(int button, int state, int x, int y)
{

}

void DefaultRenderer::processMouseMove(int x, int y)
{

}

void DefaultRenderer::processMenuEvents(int option)
{
    (void)option;
    /*do nothing for now.*/
}

bool DefaultRenderer::createMenus()
{
    return false;
}

void DefaultRenderer::addMenus() 
{}


