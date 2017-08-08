#pragma once
#include "DefaultRenderer.h"

class SnowmanRenderer : public DefaultRenderer
{
public:
    void renderScene(void) override;
    void processSpecialKeys(int key, int x, int y) override;
    void processReleaseKey(int key, int x, int y) override;

    void processMouseButton(int button, int state, int x, int y) override;
    void processMouseMove(int x, int y) override;

    SnowmanRenderer();

private:
    void drawSnowman();
    void computePos(float deltaMove);
    void computeDir(float deltaAngle);

private:
    float angle; //angle of rotation for the camera direction
    float lx, lz; //actual vector representing the camera's direction
    float x, z; //XZ position of the camera
    float deltaAngle;
    float deltaMove;
    int xOrigin;
};

