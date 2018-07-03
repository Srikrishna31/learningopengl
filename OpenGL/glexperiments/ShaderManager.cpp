#include "stdafx.h"
#include "ShaderManager.h"
#include <fstream>
using namespace  std;


ShaderManager::ShaderManager()
    : m_v(glCreateShader(GL_VERTEX_SHADER))
    , m_g(glCreateShader(GL_GEOMETRY_SHADER))
    , m_f(glCreateShader(GL_FRAGMENT_SHADER))
{

}

ShaderManager::~ShaderManager()
{

}

string ShaderManager::loadShaderFile(const string& path)
{
    ifstream file(path);
    return string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

GLuint ShaderManager::generateProgramId() {
    return glCreateProgram();
}

bool ShaderManager::loadShader(const std::string& path, const ShaderType type, const GLuint program)
{
    GLuint s = -1;
    switch (type) {
    case ShaderType::VERTEX:
        s = glCreateShader(GL_VERTEX_SHADER);
        break;
    case ShaderType::FRAGMENT:
        s = glCreateShader(GL_FRAGMENT_SHADER);
        break;
    case ShaderType::GEOMETRY:
        s = glCreateShader(GL_GEOMETRY_SHADER);
        break;
    //case ShaderType::TESSELLATION:
    //    //s = glCreateShader(GL_TESSELLATION_SHADER);
    //    break;
    default:
        assert(!"Unsupported shader type");
    }

    auto content = loadShaderFile(path);

    auto c = content.c_str();
    glShaderSource(s, 1, &c, nullptr);

    glCompileShader(s);

    glAttachShader(program, s);

    glLinkProgram(program);
    glUseProgram(program);

    return true;
}

