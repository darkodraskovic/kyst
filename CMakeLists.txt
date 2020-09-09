# cmake ..
cmake_minimum_required(VERSION 3.8)
project(opengl-cg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Engine
file(GLOB_RECURSE ENGINE_C "Engine/*.c" "Engine/*.cpp")
set(ENGINE_H "." "Graphics" "Scene" "Collision")

add_library(engine SHARED ${ENGINE_C})
target_include_directories(engine PUBLIC ${ENGINE_H})
target_link_libraries(engine GL GLU glfw dl)

# ShapeFactory
file(GLOB SHAPE_FACTORY_C "ShapeFactory/*.cpp")

add_library(shapeFactory SHARED ${SHAPE_FACTORY_C})
target_include_directories(shapeFactory PUBLIC ".")
target_link_libraries(shapeFactory PRIVATE engine)

# Samples
function(add_target TARGET)
  file(GLOB APP_C "Samples/${TARGET}/*.cpp")
  add_executable(${TARGET} ${APP_C})
  target_include_directories(${TARGET} PUBLIC "${TARGET}/")
  target_link_libraries(${TARGET} GL GLU glfw dl engine shapeFactory)
endfunction()

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

# make 07_Bounce && ./07_Bounce
add_target(07_Bounce)
