#pragma once
#include "DefaultRenderer.h"

class TriangleShaderRenderer final : public DefaultRenderer
{
private:
    std::unique_ptr<struct Impl> data;
    
    void updateModelViewProjectionMatrix();
public:
    void setPerspective(int w, int h, float aspectRatio) override;

    TriangleShaderRenderer();
    ~TriangleShaderRenderer();

    void renderScene(void) override;
    void processNormalKeys(std::uint8_t key, int x, int y) override;
    void processSpecialKeys(int key, int x, int y) override;
};