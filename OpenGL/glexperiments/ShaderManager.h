#pragma once

class ShaderManager {
private:
    GLuint m_v, m_g, m_f;

public:
    enum class ShaderType{
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        //TESSELLATION
    };

    ShaderManager();
    ~ShaderManager();

    auto loadShader(const std::string& content, const ShaderType type, const GLuint program) -> bool;

    auto generateProgramId()->GLuint;

private:
    auto loadShaderFile(const std::string& path) ->std::string;
};