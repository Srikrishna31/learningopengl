#pragma once
#include "ISceneRenderer.h"

class TriangleRenderer : public ISceneRenderer
{
private:
    float angle = 0.0f;
    float red = 1.0f;
    float green = 1.0f;
    float blue = 1.0f;

public:
    void renderScene(void) override;
    void windowResized(int w, int h) override;
    void processNormalKeys(std::uint8_t key, int x, int y) override;
    void processSpecialKeys(int key, int x, int y) override;

};