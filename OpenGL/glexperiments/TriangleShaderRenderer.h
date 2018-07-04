#pragma once
#include "DefaultRenderer.h"

class TriangleShaderRenderer final : public DefaultRenderer
{
private:
    float angle = 0.0f;
    float red = 1.0f;
    float green = 1.0f;
    float blue = 1.0f;

    GLuint program = 0;
    GLuint vertShader = 0;
    GLuint fragShader = 0;

public:
    TriangleShaderRenderer();
    ~TriangleShaderRenderer();

    void renderScene(void) override;
    void processNormalKeys(std::uint8_t key, int x, int y) override;
    void processSpecialKeys(int key, int x, int y) override;
};