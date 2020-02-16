#pragma once

class ISceneRenderer
{
public:
    virtual ~ISceneRenderer() = default;
    
    virtual void renderScene(void) = 0;
    virtual void windowResized(int w, int h) = 0;
    virtual void setPerspective(int w, int h, float aspectRatio) = 0;
    
    virtual void processNormalKeys(uint8_t key, int x, int y) = 0;
    virtual void processSpecialKeys(int key, int x, int y) = 0;
    virtual void processReleaseKey(int key, int x, int y) = 0;
    
    virtual void processMouseButton(int button, int state, int x, int y) = 0;
    virtual void processMouseMove(int x, int y) = 0;

    virtual void processMenuEvents(int option) = 0;
    // function called by client so that any class wishing to create a menu can do so.
    virtual bool createMenus() = 0; 
    virtual void addMenus() = 0;
};