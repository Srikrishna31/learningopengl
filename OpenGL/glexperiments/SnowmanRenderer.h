#pragma once
#include "DefaultRenderer.h"

class SnowmanRenderer : public DefaultRenderer
{
    friend void processFillMenu(int );
    friend void processShrinkMenu(int);
    friend void processColorMenu(int);
public:
    void renderScene(void) override;
    void processSpecialKeys(int key, int x, int y) override;
    void processReleaseKey(int key, int x, int y) override;

    void processMouseButton(int button, int state, int x, int y) override;
    void processMouseMove(int x, int y) override;

    void windowResized(int w, int h) override;

    void processMenuEvents(int option) override; 
    bool createMenus() override;
    void addMenus() override;

    SnowmanRenderer();

private:
    void drawSnowman();
    void computePos(float deltaMove);
    void computeDir(float deltaAngle);

    void processShrinkMenu(int option);
    void processFillMenu(int option);
    void processColorMenu(int option);

private:
    float   angle; //angle of rotation for the camera direction
    float   lx, lz; //actual vector representing the camera's direction
    float   x, z; //XZ position of the camera
    float   deltaAngle;
    float   deltaMove;
    int     xOrigin;
    float   red;
    float   green;
    float   blue;
};

