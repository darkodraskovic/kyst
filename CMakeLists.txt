cmake_minimum_required(VERSION 3.8)
project(opengl-cg)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SAMPLES "Source/Samples")

# libraries
add_subdirectory("Source/Engine")
add_subdirectory("Source/ShapeFactory")

# make 00_BasicApp && ./00_BasicApp
file(GLOB BASIC_APP_C "${SAMPLES}/00_BasicApp/*.cpp")
add_executable(00_BasicApp ${BASIC_APP_C})
target_include_directories(00_BasicApp PUBLIC "${SAMPLES}/00_BasicApp/")
target_link_libraries(00_BasicApp GL GLU glfw dl engine shapeFactory)

# make 01_Cube && ./01_Cube
file(GLOB CUBE_C "${SAMPLES}/01_Cube/*.cpp")
add_executable(01_Cube ${CUBE_C})
target_include_directories(01_Cube PUBLIC "${SAMPLES}/01_Cube/")
target_link_libraries(01_Cube GL GLU glfw dl engine shapeFactory)

# make 02_Sierpinski && ./02_Sierpinski
file(GLOB SIERPINSKI_C "${SAMPLES}/02_Sierpinski/*.cpp")
add_executable(02_Sierpinski "${SIERPINSKI_C}")
target_include_directories(02_Sierpinski PUBLIC "${SAMPLES}/02_Sierpinski")
target_link_libraries(02_Sierpinski GL GLU glfw dl engine shapeFactory)

# make 03_Shapes2D && ./03_Shapes2D
file(GLOB SHAPES2D_C "${SAMPLES}/03_Shapes2D/*.cpp")
add_executable(03_Shapes2D "${SHAPES2D_C}")
target_include_directories(03_Shapes2D PUBLIC "${SAMPLES}/03_Shapes2D")
target_link_libraries(03_Shapes2D GL GLU glfw dl engine shapeFactory)

# make 04_Maze && ./04_Maze
file(GLOB MAZE_C "${SAMPLES}/04_Maze/*.cpp")
add_executable(04_Maze "${MAZE_C}")
target_include_directories(04_Maze PUBLIC "${SAMPLES}/04_Maze")
target_link_libraries(04_Maze GL GLU glfw dl engine shapeFactory)

# make 05_GenArt && ./05_GenArt
file(GLOB GENART_C "${SAMPLES}/05_GenArt/*.cpp")
add_executable(05_GenArt ${GENART_C})
target_include_directories(05_GenArt PUBLIC "${SAMPLES}/05_GenArt/")
target_link_libraries(05_GenArt GL GLU glfw dl engine shapeFactory)
