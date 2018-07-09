#include "stdafx.h"
#include "TriangleShaderRenderer.h"
#include "ShaderManager.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//Internal structure holding data for the class.
struct Impl {
    float angle = 0.0f;
    float red = 1.0f;
    float green = 1.0f;
    float blue = 1.0f;

    GLuint program = 0;
    GLuint vertShader = 0;
    GLuint fragShader = 0;

    glm::mat4 perspective = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    glm::mat4 vp = glm::mat4(1.0f);
};

void TriangleShaderRenderer::updateModelViewProjectionMatrix()
{
    data->vp = data->perspective * data->view;
}

TriangleShaderRenderer::TriangleShaderRenderer()
    : data(std::make_unique<Impl>())
{
    data->program = ShaderManager::generateProgramId();

    data->view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), //Eye coordinates
        glm::vec3(0.0f, 0.0f, 0.0f), //Point at which Eye is looking.
        glm::vec3(0.0f, 1.0f, 0.0f)); //Up direction.

    updateModelViewProjectionMatrix();
    //Load order of shaders should be maintained: first is vertex and then fragment, since the variables defined in 
    //vertex shader could be used by fragment shader.
    ShaderManager::loadShader("D:/Personal/Code/Learning_OpenGL_new/OpenGL/glexperiments/shaders/vertex.vert", ShaderManager::ShaderType::VERTEX, data->program);
    ShaderManager::loadShader("D:/Personal/Code/Learning_OpenGL_new/OpenGL/glexperiments/shaders/fragment.frag", ShaderManager::ShaderType::FRAGMENT, data->program);

    ShaderManager::printShaderInfo(data->program);

    GLint vertexLoc = glGetAttribLocation(data->program, "position");

    //Data set for a set of triangles
    float pos[] = { -2.0f, -2.0f, 0.0f, 1.0f,
                   2.0f, 0.0f, 0.0f, 1.0f,
                   0.0f, 2.0f, 0.0f, 1.0f };
    
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


    glUseProgram(data->program);
    glBindVertexArray(vao);
}

void TriangleShaderRenderer::windowResized(int w, int h)
{
    //Prevent divide by 0 when window is too short
    if (h == 0)
        h = 1;

    auto ratio = 1.0f*w / h;

    glViewport(0, 0, w, h);

    data->perspective = glm::perspective(45.0f, ratio, 1.0f, 1000.0f);
    updateModelViewProjectionMatrix();

}

TriangleShaderRenderer::~TriangleShaderRenderer()
{
}

void TriangleShaderRenderer::renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
    auto modelview = glm::translate(data->vp, glm::vec3(0.0f, 0.0f, 5.0f));
    modelview = glm::rotate(modelview, data->angle, glm::vec3(0.0f, 1.0f, 0.0f));
    //modelview = glm::translate(data->vp, glm::vec3(0.0f, 0.0f, 5.0f));
    //GLuint matricesBlock = glGetUniformBlockIndex(data->program, "Matrices");
    ////the bindingPoint must be smaller than GL_MAX_UNIFORM_BUFFER_BINDING
    //GLuint bindingPoint = 1, buffer;
    //glGenBuffers(1, &buffer);
    //glUniformBlockBinding(data->program, matricesBlock, bindingPoint);
    //glBindBuffer(GL_UNIFORM_BUFFER, buffer);

    //glBufferData(GL_UNIFORM_BUFFER, sizeof(modelview), &modelview[0][0], GL_DYNAMIC_DRAW);



    GLint uniLoc = glGetUniformLocation(data->program, "pvm");
    //Need to transpose the values so that the column major order is restored.
    glUniformMatrix4fv(uniLoc, 1, GL_TRUE, &modelview[0][0]);


    GLint color = glGetUniformLocation(data->program, "color");
    glUniform4fv(color, 1, &(glm::vec4(data->red, data->green, data->blue, 1.0f)[0]));

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    glutSwapBuffers();

    //data->angle += 0.1f;
    data->angle += 0.005f;
}

void TriangleShaderRenderer::processNormalKeys(std::uint8_t key, int x, int y)
{
    if (key == 27)
        exit(0);
    else if (key == 'r')
    {
        auto mod = glutGetModifiers();
        data->red = mod == GLUT_ACTIVE_ALT ? 0.0f : 1.0f;
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
            data->red = 1.0f;
            data->green = 0.0f;
            data->blue = 0.0f;
        }
    }
    break;
    case GLUT_KEY_F2:
        data->red = 0.0f;
        data->green = 1.0f;
        data->blue = 0.0f;
        break;

    case GLUT_KEY_F3:
        data->red = 0.0f;
        data->green = 0.0f;
        data->blue = 1.0f;
        break;
    }
}
