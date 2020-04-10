cmake_minimum_required(VERSION 3.8)
project (opengl-cg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE "Source")
set(ENGINE "${SOURCE}/Engine")
set(SAMPLES "${SOURCE}/Samples")
set(SHAPE_FACTORIES "${SOURCE}/ShapeFactories")

include_directories(
  ${ENGINE}
  "${ENGINE}/Scene"
  "${ENGINE}/Graphics"
  ${SHAPE_FACTORIES})
file(GLOB_RECURSE ENGINE_C "${ENGINE}/*.c" "${ENGINE}/*.cpp")
file(GLOB SHAPE_FACTORIES_C "${SHAPE_FACTORIES}/*.cpp")

# 01_Cube
file(GLOB CUBE_SOURCES
  ${ENGINE_C} ${SHAPE_FACTORIES_C}
  "${SAMPLES}/01_Cube/*.cpp")
add_executable(01_Cube "${CUBE_SOURCES}")
target_include_directories(01_Cube PUBLIC "${SAMPLES}/01_Cube")
target_link_libraries(01_Cube GL GLU glfw dl)

# 02_Sierpinski
file(GLOB SIERPINSKI_SOURCES
  ${ENGINE_C} ${SHAPE_FACTORIES_C}
  "${SAMPLES}/02_Sierpinski/*.cpp")
add_executable(02_Sierpinski "${SIERPINSKI_SOURCES}")
target_include_directories(02_Sierpinski PUBLIC "${SAMPLES}/02_Sierpinski")
target_link_libraries(02_Sierpinski GL GLU glfw dl)
