#include <cstdint>
#include "SnowmanRenderer.h"
#include "GL/glut.h"
#include <math.h>

SnowmanRenderer::SnowmanRenderer()
    : angle(0.0f)
    , lx(0.0f)
    , lz(-1.0f)
    , x(0.0f)
    , z(5.0f)
    , deltaAngle(0.0f)
    , deltaMove(0.0f)
{}

void SnowmanRenderer::drawSnowman()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    //Draw Body
    glTranslatef(0.0f, 0.75f, 0.0f);
    glutSolidSphere(0.75f, 20, 20);
    
    //Draw head
    glTranslatef(0.0f, 1.0f, 0.0f);
    glutSolidSphere(0.25f, 20, 20);

    //Draw eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.05f, 0.10f, 0.18f);
    glutSolidSphere(0.05f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.05f, 10, 10);
    glPopMatrix();

    //Draw nose
    glColor3f(1.0f, 0.5f, 0.5f);
    glutSolidCone(0.08f, 0.5f, 10, 2);
}

void SnowmanRenderer::renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    gluLookAt(x, 1.0f, z,
        x + lx, 1.0f, z + lz,
        0.0f, 1.0f, 0.0f);

    //draw ground
    glColor3f(0.9f, 0.9f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(-100.0f, 0.0f, -100.0f);
    glVertex3f(-100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, 100.0f);
    glVertex3f(100.0f, 0.0f, -100.0f);
    glEnd();

    //Draw 36 snowmen
    for (auto i = -3; i < 3; ++i)
    {
        for (auto j = -3; j < 3; ++j)
        {
            glPushMatrix();
            glTranslatef(i*10.0f, 0, j*10.0f);
            drawSnowman();
            glPopMatrix();
        }
    }

    glutSwapBuffers();

}

void SnowmanRenderer::processSpecialKeys(int key, int x, int y)
{
    const auto fraction = 0.1f;

    switch (key) {
    case GLUT_KEY_LEFT:
        angle -= 0.01f;
        lx = static_cast<float>(sin(angle));
        lz = static_cast<float>(-cos(angle));
        break;
    case GLUT_KEY_RIGHT:
        angle += 0.01f;
        lx = static_cast<float>(sin(angle));
        lz = static_cast<float>(-cos(angle));
        break;
    case GLUT_KEY_UP:
        this->x += lx * fraction;
        this->z += lz * fraction;
        break;
    case GLUT_KEY_DOWN:
        this->x -= lx * fraction;
        this->z -= lz * fraction;
        break;
    }
}
