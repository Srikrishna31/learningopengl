#pragma once

namespace ShaderManager {

    enum class ShaderType
    {
        VERTEX,
        FRAGMENT,
        GEOMETRY,
        //TESSELLATION
    };

    auto loadShader(const std::string& content, const ShaderType type, const GLuint program) -> bool;

    auto generateProgramId() -> GLuint;

    auto printShaderInfo(GLuint program) -> void;

};