This project is a simple exploration of OpenGL capabilities.

It relies on the following 3rd party libraries (that are checked into the source):
1. freeglut-3.0.0  : Provides cross platform windowing toolkit, to explore OpenGL without the headache of choosing one.
2. glew-2.0.0: A library that allows to query the version and other capabilities of underlying OpenGL implementation.
3. glm: A simple math library, that mimics GLSL style functions, so that matrix manipulations are easy.

For Windows, the prerequisites are:
1. VS 2017 or later with CMake support.
2. Note that the commandline arguments can be passed to the executable based on the explanation given here: https://docs.microsoft.com/en-us/cpp/ide/cmake-tools-for-visual-cpp?view=vs-2017

For Linux(Ubuntu), the prerequisites are:
1. OpenGL headers and libraries, which can be installed with: "sudo apt install libgl1-mesa-dev" and "sudo apt install mesa-utils" to check the OpenGL version, which can be done with this command: glxinfo | grep "OpenGL version".

