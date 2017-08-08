#include<iostream>
#include "glew.h"
#include <GL/glut.h>
#include <gl/GL.h>
#include "TriangleRenderer.h"
#include "SnowmanRenderer.h"
#include <memory>
#include <vector>
#include <string>
/*
GLUT tutorial from this site:
http://www.lighthouse3d.com/tutorials/glut-tutorial/initialization/
*/

std::unique_ptr<ISceneRenderer> pRenderer = nullptr;

std::vector<std::string> gl_versions = { "4_5", "4_4", "4_3", "4_2", "4_1", "4_0", "3_3", "3_2", "3_1", "3_0", "2_1", "1_5", "1_4", "1_3", "1_2_1", "1_2", "1_1", "1_0" };

using namespace std::string_literals;

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

void processReleaseKey(int key, int x, int y)
{
    pRenderer->processReleaseKey(key, x, y);
}

void processMousePress(int button, int state, int x, int y)
{
    pRenderer->processMouseButton(button, state, x, y);
}

void processMouseMove(int x, int y)
{
    pRenderer->processMouseMove(x, y);
}

void getGLInfo()
{
    auto err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << std::endl << "Error initializing glew: " << glewGetErrorString(err) << std::endl;
    }

    std::cout << std::endl << "Using GLEW: " << glewGetString(GLEW_VERSION) << std::endl;

    auto versionString = "GL_VERSION_"s;
    auto i = 0;
    for (auto ver : gl_versions)
    {
        if (glewIsSupported((versionString + ver).c_str()))
        {
            std::cout << "\nOpenGL version : " << ver.c_str() << std::endl;
            if (i <= 9) //if version > 3.0
            {
                std::cout << std::endl << "Vendor: " << glGetString(GL_VENDOR);
                std::cout << std::endl << "Renderer: " << glGetString(GL_RENDERER);
                std::cout << std::endl << "Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION);
            }
            break;
        }
        ++i;
    }
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
    glutMouseFunc(processMousePress);
    glutMotionFunc(processMouseMove);


    // OpenGL init
    glEnable(GL_DEPTH_TEST);

    glutMainLoop();

    return 0;
}

