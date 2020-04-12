# OpenGL Computer Graphics

A minimal OpenGL based graphics library plus random computer graphics and
generative art samples.

Includes selected solutions for [Interactive Computer Graphics: A Top-Down
Approach with WebGL, 7th
Edition](https://www.pearson.com/us/higher-education/product/Angel-Interactive-Computer-Graphics-A-Top-Down-Approach-with-Web-GL-7th-Edition/9780133574845.html).

## Installation

On Ubuntu, install the following libraries:

```
apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev libxi-dev
```

Install [Glad library](https://github.com/Dav1dde/glad.git), a
GL/GLES/EGL/GLX/WGL Loader-Generator:

```
git clone https://github.com/Dav1dde/glad.git 
cd glad 
cmake ./ 
make 
sudo cp -a include /usr/local/
```

Copy *glad.c* from *glad/src/* git cloned source directory to the project
*Source/Engine/* directory.

Install [STB library](https://github.com/nothings/stb) for image handling:

```
git clone https://github.com/nothings/stb.git 
cd stb
sudo mkdir /usr/local/include/stb
sudo cp -a stb* /usr/local/include/stb/
```

## Build

In order to compile a specific example, `mkdir build`, `cd build` and run

```cmake ../```

After the successful creation of the *Makefile* build the examples with

```make <example> && ./example```

where <sample> stands for the name of the corresponding sample directory. E.g.
to make and run *01_Cube* run

```make 01_Cube && ./01_Cube```
