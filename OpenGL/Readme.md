This project is a simple exploration of OpenGL capabilities.
Make sure to install bazel from here: https://docs.bazel.build/versions/4.0.0/install.html

In addition, the project relies on the following 3rd party libraries:
1. freeglut-3.0.0  : Provides cross platform windowing toolkit, to explore OpenGL without the headache of choosing one.
2. glew-2.0.0: A library that allows to query the version and other capabilities of underlying OpenGL implementation.
3. glm: A simple math library, that mimics GLSL style functions, so that matrix manipulations are easy.
4. Assimp: A library to load 3D models(Collada, 3DS etc).

For Windows, the prerequisites are:
	1. VS 2017 or later.
	2. Note that the commandline arguments can be passed to the executable based on the explanation given here: https://docs.microsoft.com/en-us/cpp/ide/cmake-tools-for-visual-cpp?view=vs-2017
	3. VSCode / CLion for editing code.

For Linux(Ubuntu), the prerequisites are:
	1. OpenGL headers and libraries, which can be installed with: "sudo apt install libgl1-mesa-dev mesa-common-dev libglu1-mesa-dev" and "sudo apt install mesa-utils" to check the OpenGL version, which can be done with this command: glxinfo | grep "OpenGL version".
	2. Install additional supporting libraries: "sudo apt install libx11-dev libxrandr-dev libxi-dev"

To build the OpenGL project, invoke bazel as below:
bazel build :glexp

To run the project, 
bazel run :glexp -- -shaders
