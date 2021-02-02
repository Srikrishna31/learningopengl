#include "stdafx.h"
#include "TriangleShaderRenderer.h"

//Internal structure holding data for the class.
struct Impl {
    float angle = 0.0f;
    float red = 1.0f;
    float green = 1.0f;
    float blue = 1.0f;

    GLuint program = 0;
    GLuint vertShader = 0;
    GLuint fragShader = 0;
    GLuint vertexAttribArray = 0;

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

    data->vertexAttribArray = ShaderManager::loadVertexArray(data->program, vertexLoc, pos, sizeof(pos), 4,
                                                             index, sizeof(index), GL_STATIC_DRAW);
}

void TriangleShaderRenderer::setPerspective(int w, int h, float aspectRatio)
{
    data->perspective = glm::perspective(45.0f, aspectRatio, 1.0f, 1000.0f);
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
    auto modelViewT = glm::transpose(modelview);
    
    GLuint matricesBlock = glGetUniformBlockIndex(data->program, "Matrices");
    //the bindingPoint must be smaller than GL_MAX_UNIFORM_BUFFER_BINDING
    GLuint bindingPoint = 1, buffer;
    glGenBuffers(1, &buffer);
    glUniformBlockBinding(data->program, matricesBlock, bindingPoint);
    glBindBuffer(GL_UNIFORM_BUFFER, buffer);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(modelViewT), &modelViewT, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);

    //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(modelview), &modelview[0][0]);

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
