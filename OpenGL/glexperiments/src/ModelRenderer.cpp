#include "stdafx.h"
#include "ModelRenderer.h"

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

/*
Information for loading model files using assimp library is taken 
from here:
http://ogldev.atspace.co.uk/www/tutorial22/tutorial22.html
*/
using namespace std;

struct Internal {
    std::string modelFilePath;
    std::unique_ptr<const aiScene> pScene;

    GLuint program = 0;
    GLuint vertShader = 0;
    GLuint fragShader = 0;

    glm::mat4 perspective = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);

    glm::mat4 vp = glm::mat4(1.0f);
};

ModelRenderer::ModelRenderer(const string& modelFilePath)
    : DefaultRenderer()
    , m_data(nullptr)
{
    Assimp::Importer importer;

    auto pScene = importer.ReadFile(modelFilePath,
        aiProcess_Triangulate | aiProcess_GenSmoothNormals |
        aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

    if (pScene) {
        m_data = std::make_unique<Internal>();
        m_data->pScene = std::unique_ptr<const aiScene>(pScene);
        m_data->modelFilePath = modelFilePath;

        if (m_data->pScene->HasCameras) {
            //Load the default camera for viewing the model.
            auto cameraMatrix = aiMatrix4x4();
            m_data->pScene->mCameras[0]->GetCameraMatrix(cameraMatrix);
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++)
                    m_data->view[i][j] = static_cast<float>(cameraMatrix[i][j]);
            }
        }
        else {
            m_data->view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f), //Eye coordinates
                glm::vec3(0.0f, 0.0f, 0.0f), //Point at which Eye is looking.
                glm::vec3(0.0f, 1.0f, 0.0f)); //Up direction.
        }
        updateModelViewProjectionMatrix();

        if (pScene->HasMeshes) {
            for (int i = 0; i < pScene->mNumMeshes; i++) {
                ShaderManager::loadVertexArray(m_data->program, m_data->)
                for (int j = 0; j < pScene->mMeshes[i]->mNumVertices; j++) {
                    pScene->mMeshes[i]->mVertices[0].
                }
            }
        }
    }
    else {
        throw InvalidModelFileException(importer.GetErrorString());
    }

    glEnable(GL_DEPTH_TEST);
}

void ModelRenderer::updateModelViewProjectionMatrix()
{
    m_data->vp = m_data->perspective * m_data->view;
}

void ModelRenderer::setPerspective(int w, int h, float aspectRatio)
{
    m_data->perspective = glm::perspective(45.0f, aspectRatio, 1.0f, 1000.0f);
    updateModelViewProjectionMatrix();
}

void ModelRenderer::renderScene(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto modelview = glm::translate(m_data->vp, glm::vec3(0.0f, 0.0f, 5.0f));
    //modelview = glm::rotate(modelview, m_data->angle, glm::vec3(0.0f, 1.0f, 0.0f));
    //modelview = glm::translate(data->vp, glm::vec3(0.0f, 0.0f, 5.0f));
    auto modelViewT = glm::transpose(modelview);

    GLuint matricesBlock = glGetUniformBlockIndex(m_data->program, "Matrices");
    //the bindingPoint must be smaller than GL_MAX_UNIFORM_BUFFER_BINDING
    GLuint bindingPoint = 1, buffer;
    glGenBuffers(1, &buffer);
    glUniformBlockBinding(m_data->program, matricesBlock, bindingPoint);
    glBindBuffer(GL_UNIFORM_BUFFER, buffer);

    glBufferData(GL_UNIFORM_BUFFER, sizeof(modelViewT), &modelViewT, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, buffer);

    //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(modelview), &modelview[0][0]);

    GLint color = glGetUniformLocation(m_data->program, "color");
    //glUniform4fv(color, 1, &(glm::vec4(m_data->red, data->green, data->blue, 1.0f)[0]));

    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
    glutSwapBuffers();

    //data->angle += 0.1f;
    //data->angle += 0.005f;
}
