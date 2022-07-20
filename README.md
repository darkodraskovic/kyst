# OpenGL Computer Graphics

A minimal OpenGL based graphics library plus random computer graphics and generative art samples.

Includes selected solutions for [Interactive Computer Graphics: A Top-Down Approach with WebGL, 7th Edition](https://www.pearson.com/us/higher-education/product/Angel-Interactive-Computer-Graphics-A-Top-Down-Approach-with-Web-GL-7th-Edition/9780133574845.html).

## Installation

### Ubuntu

On Ubuntu, install the following libraries:

```
apt-get install libsoil-dev libglm-dev libassimp-dev libglew-dev libglfw3-dev libxinerama-dev libxcursor-dev libxi-dev
```

Install [Glad library](https://github.com/Dav1dde/glad.git), a GL/GLES/EGL/GLX/WGL Loader-Generator:

```
git clone https://github.com/Dav1dde/glad.git
cd glad && make build && cd build
cmake ../
make
# the -a option means -R and -p, plus same directory tree, same file types, same contents, same metadata
sudo cp -a include /usr/local/
```

Copy *glad.c* from *build/src/* git cloned source directory to the project *Source/Engine/* directory.

Install [STB library](https://github.com/nothings/stb) for image handling:

```
git clone https://github.com/nothings/stb.git
cd stb
sudo mkdir /usr/local/include/stb
sudo cp -a stb* /usr/local/include/stb/
```

### Windows

Make dir `lib`, `cd` into `lib` and

```
git clone https://github.com/g-truc/glm
git clone https://github.com/nothings/stb
```

Go to https://glad.dav1d.de/ and choose `C/C++` as Language, `OpenGL` as Specification, `Core` Profile and API `Version 3.3`. Download `glad.zip` and unzip it into `glad` dir in `lib` dir. Copy `lib\glad\src\glad.c` in `kyst\Source\Engine`. 

Download [GLFW Windows pre-compiled binaries](https://www.glfw.org/download) and unzip it into `lib\glfw` dir.

## Build

In order to compile a specific example, `mkdir build`, `cd build` and run

```
cmake ../
```

After the successful creation of the *Makefile* build the examples with

```
make <example> && ./example <example>
```

where <sample> stands for the name of the corresponding sample directory. E.g. to make and run *01_Cube* run

```
make 01_Cube && cd ../bin && ./01_Cube
```

### Windows

```
# configure

cd build && cmake ..

# build

cd build && MSBuild.exe -target:Build /property:Configuration=Release <target>.vcxproj

# or

cd build && MSBuild.exe -target:Build /property:Configuration=Release kyst.sln

# run

cd bin/ && <target>.exe
```

## Boilerplate

For the minimal app, see `Source/Samples/00_BasicApp`. For other examples, see `Source/Samples/`.
