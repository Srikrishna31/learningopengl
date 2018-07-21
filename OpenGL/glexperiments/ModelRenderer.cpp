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
    }
    else {
        throw InvalidModelFileException(importer.GetErrorString());
    }
}

