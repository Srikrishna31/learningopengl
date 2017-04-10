#pragma once
#include "ISceneRenderer.h"

class DefaultRenderer : public ISceneRenderer
{
public:
    virtual ~DefaultRenderer() = default;

    virtual void renderScene(void) override;
    virtual void windowResized(int w, int h) override;
    virtual void processNormalKeys(uint8_t key, int x, int y) override;
    virtual void processSpecialKeys(int key, int x, int y) override;

};
