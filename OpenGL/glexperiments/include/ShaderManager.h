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

    /**
    This function generates a VertexAttribArray, and loads all the vertices passed in, into the shader.
    @param program - the shader program associated.
    @param program vertexLoc - the location of the vertices in the shader program
    @param vertices - array of vertices 
    @param numVertices - total size of the vertexBlock, that is being passed in.
    @param vertexComponents - number of components in a vertex - 2D/3D/4D
    @param indices - array of indices describing how to connect the vertices.
    @param numIndices - total size of the indexBlock, that is being passed in.
    @param DRAW_TYPE - the type of drawing that is intended eg. GL_DYNAMIC_DRAW / GL_STATIC_DRAW.
    */
    auto loadVertexArray(const GLuint program, const GLint vertexLoc, const float* vertices, const uint32_t numVertices, 
                             const uint8_t vertexComponents, const uint32_t* indices, const uint32_t numIndices, const uint32_t DRAW_TYPE) -> GLuint;
};