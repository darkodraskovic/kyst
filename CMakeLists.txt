cmake_minimum_required(VERSION 3.8)
project(opengl-cg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SAMPLES "Source/Samples")

# libraries
add_subdirectory("Source/Engine")
add_subdirectory("Source/ShapeFactory")

# 01_Cube
file(GLOB CUBE_C "${SAMPLES}/01_Cube/*.cpp")
add_executable(01_Cube ${CUBE_C})
target_include_directories(01_Cube PUBLIC "${SAMPLES}/01_Cube/")
target_link_libraries(01_Cube GL GLU glfw dl engine shapeFactory)

# 02_Sierpinski
file(GLOB SIERPINSKI_C "${SAMPLES}/02_Sierpinski/*.cpp")
add_executable(02_Sierpinski "${SIERPINSKI_C}")
target_include_directories(02_Sierpinski PUBLIC "${SAMPLES}/02_Sierpinski")
target_link_libraries(02_Sierpinski GL GLU glfw dl engine shapeFactory)

# 03_Shapes2D
file(GLOB SHAPES2D_C "${SAMPLES}/03_Shapes2D/*.cpp")
add_executable(03_Shapes2D "${SHAPES2D_C}")
target_include_directories(03_Shapes2D PUBLIC "${SAMPLES}/03_Shapes2D")
target_link_libraries(03_Shapes2D GL GLU glfw dl engine shapeFactory)

file(GLOB MAZE_C "${SAMPLES}/04_Maze/*.cpp")
add_executable(04_Maze "${MAZE_C}")
target_include_directories(04_Maze PUBLIC "${SAMPLES}/04_Maze")
target_link_libraries(04_Maze GL GLU glfw dl engine shapeFactory)
