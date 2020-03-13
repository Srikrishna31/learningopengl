#include "stdafx.h"
#include <cstdint>
#include "TriangleRenderer.h"

void TriangleRenderer::renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity(); //Clear the transformation matrix.

    gluLookAt(0.0f, 0.0f, 10.0f, // Eye coordinates
        0.0f, 0.0f, 0.0f, //Point at which Eye is looking.
        0.0f, 1.0f, 0.0f); //Up direction for the eye.

    glRotatef(angle, 0.0f, 1.0f, 0.0f);
    glColor3f(red, green, blue);
    glBegin(GL_TRIANGLES);
    glVertex3f(-2.0f, -2.0f, -5.0f);
    glVertex3f(2.0f, 0.0f, -5.0f);
    glVertex3f(0.0f, 2.0f, -5.0f);
    glEnd();

    glutSwapBuffers();

    angle += 0.1f;
}

void TriangleRenderer::processNormalKeys(std::uint8_t key, int x, int y)
{
    if (key == 27)
        exit(0);
    else if (key == 'r')
    {
        auto mod = glutGetModifiers();
        red = mod == GLUT_ACTIVE_ALT ? 0.0f : 1.0f;
    }
}

void TriangleRenderer::processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F1:
    {
        auto mod = glutGetModifiers();
        if (mod == (GLUT_ACTIVE_ALT | GLUT_ACTIVE_CTRL))
        {
            red = 1.0f;
            green = 0.0f;
            blue = 0.0f;
        }
    }
    break;
    case GLUT_KEY_F2:
        red = 0.0f;
        green = 1.0f;
        blue = 0.0f;
        break;

    case GLUT_KEY_F3:
        red = 0.0f;
        green = 0.0f;
        blue = 1.0f;
        break;
    }
}
