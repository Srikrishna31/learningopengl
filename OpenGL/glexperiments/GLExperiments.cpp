#include<iostream>
#include "glew.h"
#include <GL/glut.h>
#include <gl/GL.h>
#include "TriangleRenderer.h"
#include "SnowmanRenderer.h"
#include <memory>
/*
GLUT tutorial from this site:
http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
*/

std::unique_ptr<ISceneRenderer> pRenderer = nullptr;

void renderScene(void)
{
    pRenderer->renderScene();
}

void windowResized(int w, int h)
{
    pRenderer->windowResized(w, h);
}

void processNormalKeys(uint8_t key, int x, int y)
{
    pRenderer->processNormalKeys(key, x, y);
}

void processSpecialKeys(int key, int x, int y)
{
    pRenderer->processSpecialKeys(key, x, y);
}

void getGLInfo()
{
    auto err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << std::endl << "Error initializing glew: " << glewGetErrorString(err) << std::endl;
    }

    std::cout << std::endl << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

    std::cout << "OpenGL 3.0 supported: " << std::boolalpha << static_cast<bool>(glewIsSupported("GL_VERSION_3_0"));

    std::cout << "\nOpenGL 4.1 supported: " << std::boolalpha << static_cast<bool>(glewIsSupported("GL_VERSION_4_1"));

}

int main(int argc, char *argv[])
{
    //pRenderer = std::make_unique<TriangleRenderer>();
    pRenderer = std::make_unique<SnowmanRenderer>();

    // init GLUT and create Window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(320, 320);
    glutCreateWindow("Lighthouse3D- GLUT Tutorial");
    
    getGLInfo();

    glutDisplayFunc(renderScene); //Called when the Paint message is received from the OS
    glutReshapeFunc(windowResized); //Called when the window is resized;
    glutIdleFunc(renderScene); //Called when the application is idle.
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);


    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

