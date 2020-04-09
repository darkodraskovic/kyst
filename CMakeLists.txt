cmake_minimum_required(VERSION 3.8)
project (opengl-cg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE "Source")
set(SOURCE_ENGINE "${SOURCE}/Engine")
set(SOURCE_SAMPLES "${SOURCE}/Samples")

# Generics
include_directories(
  "${SOURCE_ENGINE}"
  "${SOURCE_ENGINE}/Scene"
  "${SOURCE_ENGINE}/Graphics")
file(GLOB SOURCE_ENGINE_C
  "${SOURCE_ENGINE}/*.c" "${SOURCE_ENGINE}/*.cpp"
  "${SOURCE_ENGINE}/Graphics/*.c" "${SOURCE_ENGINE}/Graphics/*.cpp"
  "${SOURCE_ENGINE}/Scene/*.c" "${SOURCE_ENGINE}/Scene/*.cpp")

# 01_Cube
file(GLOB CUBE_SOURCES ${SOURCE_ENGINE_C} "${SOURCE_SAMPLES}/01_Cube/*.cpp")
add_executable(01_Cube ${CUBE_SOURCES})
target_include_directories(01_Cube PUBLIC CUBE_SOURCES)
target_link_libraries(01_Cube GL GLU glfw dl)
