#include "stdafx.h"
#include "TriangleShaderRenderer.h"
#include "ShaderManager.h"

TriangleShaderRenderer::TriangleShaderRenderer()
{
    program = ShaderManager::generateProgramId();

    //Load order of shaders should be maintained: first is vertex and then fragment, since the variables defined in 
    //vertex shader could be used by fragment shader.
    ShaderManager::loadShader("D:/Personal/Code/Learning_OpenGL_new/OpenGL/glexperiments/shaders/vertex.vert", ShaderManager::ShaderType::VERTEX, program);
    ShaderManager::loadShader("D:/Personal/Code/Learning_OpenGL_new/OpenGL/glexperiments/shaders/fragment.frag", ShaderManager::ShaderType::FRAGMENT, program);

    ShaderManager::printShaderInfo(program);

    GLint vertexLoc = glGetAttribLocation(program, "position");

    //Data set for a set of triangles
    float pos[] = { -1.0f, 0.0f, -5.0f, 1.0f,
                   1.0f, 0.0f, -5.0f, 1.0f,
                   0.0f, 2.0f, -5.0f, 1.0f };
    
    float textureCoord[] = { 0.0f };
    float normal[] = { 1.0f };

    uint32_t index[] = { 0, 1, 2 };

    /*
    Attribute initialization
    */
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLuint buffer;
    glGenBuffers(1, &buffer);
    
    //bind buffer for positions and copy data into buffer
    //GL_ARRAY_BUFFER is the buffer we use to feed attributes.
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    //feed the buffer, and let OpenGL know that we don't plan to 
    //change it (STATIC) and that it will be used for drawing (DRAW)
    glBufferData(GL_ARRAY_BUFFER, sizeof(pos), pos, GL_STATIC_DRAW);
 
    //Enable the attribute at that location 
    glEnableVertexAttribArray(vertexLoc);

    //Tell OpenGL what the array contains:
    //It is a set of 4 floats for each vertex.
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);

    GLuint indBuffer;
    glGenBuffers(1, &indBuffer);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);


    /*
    Uniform initialization
    */
    GLint uniLoc = glGetUniformLocation(program, "color");
    glProgramUniform4f(program, uniLoc, red, green, blue, 1.0f);

    glUseProgram(program);
    glBindVertexArray(vao);
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
    //glColor3f(red, green, blue);

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    glutSwapBuffers();

    angle += 0.1f;
}

void TriangleShaderRenderer::processNormalKeys(std::uint8_t key, int x, int y)
{
    if (key == 27)
        exit(0);
    else if (key == 'r')
    {
        auto mod = glutGetModifiers();
        red = mod == GLUT_ACTIVE_ALT ? 0.0f : 1.0f;
    }
}

void TriangleShaderRenderer::processSpecialKeys(int key, int x, int y)
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