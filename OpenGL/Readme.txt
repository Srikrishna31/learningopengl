This project is a simple exploration of OpenGL capabilities.

It relies on the following 3rd party libraries:
1. freeglut-3.0.0  : Provides cross platform windowing toolkit, to explore OpenGL without the headache of choosing one.
2. glew-2.0.0: A library that allows to query the version and other capabilities of underlying OpenGL implementation.
3. glm: A simple math library, that mimics GLSL style functions, so that matrix manipulations are easy.
<<<<<<< HEAD

For Windows, the prerequisites are:
1. VS 2017 or later with CMake support.
2. Note that the commandline arguments can be passed to the executable based on the explanation given here: https://docs.microsoft.com/en-us/cpp/ide/cmake-tools-for-visual-cpp?view=vs-2017

For Linux(Ubuntu), the prerequisites are:
1. OpenGL headers and libraries, which can be installed with: "sudo apt install libgl1-mesa-dev" and "sudo apt install mesa-utils" to check the OpenGL version, which can be done with this command: glxinfo | grep "OpenGL version".

=======
4. Assimp: A library to load 3D models(Collada, 3DS etc).

freeglut, glew and glm sources are included in the project and they are built along with it.

Assimp library can be downloaded from here: http://assimp.org/index.php/downloads
You can download prebuilt binaries, or download the source and build it. It is recommended to download the source and build it,
so that you can choose the configuration to build for. Steps for building Assimp library:
1. Download the source and unzip it to a convenient location.
2. Create a build directory alongside that folder.
3. Enter the following command on commandline: 
	 cmake -G "Visual Studio 15 Win64" -DCMAKE_BUILD_TYPE="<config>" -DCMAKE_INSTALL_PREFIX="<path-to-copy-binaries-to>" ../../
	a. <config> can be any config that cmake supports like Debug, Release, RelWithDebInfo etc.
	b. <path-to-copy-binaries-to>: make sure that the path you are providing has write permissions, otherwise cmake will error out.
4. Open the Visual Studio project, and build the project.
5. Then also build the "INSTALL" project, as it is not set to build with the project by default.
6. Check that the directory provided in <path-to-copy-binaries-to> has all the folders - include, lib and bin.

To build the OpenGL project, invoke cmake as below:
cmake -G "Visual Studio 15 Win64" -DCMAKE_BUILD_TYPE="Debug" -DASSIMP_PATH=<path-to-copy-binaries-to> ../
>>>>>>> 223ae192052b3944c2443b59ed47c7570d3c8d00
