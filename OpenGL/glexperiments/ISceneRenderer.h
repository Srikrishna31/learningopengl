#pragma once

class ISceneRenderer
{
public:
    virtual ~ISceneRenderer() = default;
    
    virtual void renderScene(void) = 0;
    virtual void windowResized(int w, int h) = 0;
    
    virtual void processNormalKeys(uint8_t key, int x, int y) = 0;
    virtual void processSpecialKeys(int key, int x, int y) = 0;
    virtual void processReleaseKey(int key, int x, int y) = 0;
    
    virtual void processMouseButton(int button, int state, int x, int y) = 0;
    virtual void processMouseMove(int x, int y) = 0;
};