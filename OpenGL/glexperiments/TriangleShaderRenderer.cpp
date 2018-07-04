#include "stdafx.h"
#include "TriangleShaderRenderer.h"
#include "ShaderManager.h"

TriangleShaderRenderer::TriangleShaderRenderer()
{
    program = ShaderManager::generateProgramId();
    //ShaderManager::loadShader("./shaders/fragment.frag", ShaderManager::ShaderType::FRAGMENT, program);
    ShaderManager::loadShader("D:/CODE/Learning_OpenGL/OpenGL/glexperiments/shaders/vertex.vert", ShaderManager::ShaderType::VERTEX, program);

    ShaderManager::printShaderInfo(program);

    glUseProgram(program);
}

TriangleShaderRenderer::~TriangleShaderRenderer()
{
}

void TriangleShaderRenderer::renderScene(void)
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

void TriangleShaderRenderer::processNormalKeys(std::uint8_t key, int x, int y)
{

}

void TriangleShaderRenderer::processSpecialKeys(int key, int x, int y)
{

}
