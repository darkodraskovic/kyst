cmake_minimum_required(VERSION 3.8)
project(opengl-cg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# utils
include("CMake/Functions.cmake")

# libraries
add_subdirectory("Source/Engine")
add_subdirectory("Source/ShapeFactory")

# make 00_BasicApp && ./00_BasicApp
add_target(00_BasicApp)

# make 01_Cube && ./01_Cube
add_target(01_Cube)

# make 02_Sierpinski && ./02_Sierpinski
add_target(02_Sierpinski)

# make 03_Shapes2D && ./03_Shapes2D
add_target(03_Shapes2D)

# make 04_Maze && ./04_Maze
add_target(04_Maze)

# make 05_GenArt && ./05_GenArt
add_target(05_GenArt)

# make 06_Maxwell && ./06_Maxwell
add_target(06_Maxwell)
