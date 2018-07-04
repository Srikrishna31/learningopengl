#include "stdafx.h"
#include <cstdint>
#include "ShaderManager.h"
#include <fstream>

using namespace  std;

auto loadShaderFile(const string& path) -> string
{
    ifstream file(path);
    return string(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());
}

auto printGLInfoLog(std::function<int32_t()> infoLengthQuery, 
                    std::function<void(int32_t, int32_t&, char*)> infoGetter)
{
    const auto infoLength = infoLengthQuery();

    if (infoLength > 0)
    {
        auto charsWritten = 0;
        char* infoLog = new char[infoLength];
        infoGetter(infoLength, charsWritten, infoLog);

        std::cout << std::string(infoLog) << std::endl;

        delete[] infoLog;
    }

}

namespace ShaderManager {

    auto generateProgramId() -> GLuint {
        return glCreateProgram();
    }

    auto printShaderInfo(GLuint program) -> void
    {
        int maxSub, maxSubU, activeS, countActiveSU;
        char name[256]; int len, numCompS;

        glGetIntegerv(GL_MAX_SUBROUTINES, &maxSub);
        glGetIntegerv(GL_MAX_SUBROUTINE_UNIFORM_LOCATIONS, &maxSubU);
        std::cout << "Max Subroutines: " << maxSub << " Max Subroutine Uniforms: " << maxSubU << std::endl;

        glGetProgramStageiv(program, GL_VERTEX_SHADER, GL_ACTIVE_SUBROUTINE_UNIFORMS, &countActiveSU);

        for (int i = 0; i < countActiveSU; ++i) {

            glGetActiveSubroutineUniformName(program, GL_VERTEX_SHADER, i, 256, &len, name);

            std::cout << "Suroutine Uniform: " << i << " name: " << name << std::endl;
            glGetActiveSubroutineUniformiv(program, GL_VERTEX_SHADER, i, GL_NUM_COMPATIBLE_SUBROUTINES, &numCompS);

            auto s = new int[(sizeof(int) * numCompS)];

            glGetActiveSubroutineUniformiv(program, GL_VERTEX_SHADER, i, GL_COMPATIBLE_SUBROUTINES, s);
            std::cout <<"Compatible Subroutines:\n";
            for (int j = 0; j < numCompS; ++j) {

                glGetActiveSubroutineName(program, GL_VERTEX_SHADER, s[j], 256, &len, name);
                std::cout << "\t" << s[j] << ", " << name << std::endl;
            }
            std::cout << std::endl;

            delete [] s;
        }
    }

    auto loadShader(const std::string& path, const ShaderType type, const GLuint program) -> bool
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

        std::cout << content;

        auto c = content.c_str();
        glShaderSource(s, 1, &c, nullptr);

        glCompileShader(s);

        printGLInfoLog([s]() {
            int32_t logLength = 0;
            int32_t success = 0;

            glGetShaderiv(s, GL_COMPILE_STATUS, &success);
            if (!success) {
                glGetShaderiv(s, GL_INFO_LOG_LENGTH, &logLength);
            }
            return logLength;
        },
            [s](int32_t logLength, int32_t& charsWritten, char* infoLog) {
            glGetShaderInfoLog(s, logLength, &charsWritten, infoLog);
        });


        glAttachShader(program, s);

        glLinkProgram(program);

        printGLInfoLog([program]() {
            int32_t logLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
            return logLength;
        },
            [program](int32_t logLength, int32_t& charsWritten, char* infoLog) {
            glGetProgramInfoLog(program, logLength, &charsWritten, infoLog);
        });

        return true;
    }
};
