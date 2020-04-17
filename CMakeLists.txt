cmake_minimum_required(VERSION 3.8)
project (opengl-cg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCE "Source")
set(ENGINE "${SOURCE}/Engine")
set(SHAPE_FACTORY "${SOURCE}/ShapeFactory")
set(SAMPLES "${SOURCE}/Samples")

# engine
file(GLOB_RECURSE ENGINE_C "${ENGINE}/*.c" "${ENGINE}/*.cpp")
set(ENGINE_H "${ENGINE}" "${ENGINE}/Graphics" "${ENGINE}/Scene")

add_library(engine SHARED ${ENGINE_C})
target_include_directories(engine PUBLIC ${ENGINE_H})
target_link_libraries(engine GL GLU glfw dl)
  
# shape factory
file(GLOB SHAPE_FACTORY_C "${SHAPE_FACTORY}/*.cpp")
set(SHAPE_FACTORY_H "${SHAPE_FACTORY}")

add_library(shapeFactory SHARED ${SHAPE_FACTORY_C})
target_include_directories(shapeFactory PUBLIC ${SHAPE_FACTORY_H})
target_link_libraries(shapeFactory PRIVATE engine)

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
