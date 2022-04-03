cmake_minimum_required(VERSION 3.8)
project(kyst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if (WIN32)
  include_directories(lib/ lib/glad/include lib/glm lib/glfw/include)
  link_directories(lib/glfw/lib-vc2019)
  link_libraries(glfw3.lib)

  set(warning_compiler_options /W3 /wd"4267" /wd"4305" /wd"4244")
  add_compile_options(${warning_compiler_options} /MD)
endif()

# Engine
file(GLOB_RECURSE ENGINE_C "Source/Engine/*.c" "Source/Engine/*.cpp")
set(ENGINE_H "." "Graphics" "Scene" "Collision")

add_library(engine STATIC ${ENGINE_C})
target_include_directories(engine PUBLIC ${ENGINE_H})
if (WIN32)
  target_link_libraries(engine OpenGL32 glfw3)
elseif(UNIX)
  target_link_libraries(engine GL GLU glfw dl)
endif()

# ShapeFactory
file(GLOB SHAPE_FACTORY_C "Source/ShapeFactory/*.cpp")

add_library(shapeFactory STATIC ${SHAPE_FACTORY_C})
target_include_directories(shapeFactory PUBLIC "Source")
target_link_libraries(shapeFactory PUBLIC engine)

# Samples
function(add_target TARGET)
  file(GLOB APP_C "Source/Samples/${TARGET}/*.cpp")
  add_executable(${TARGET} ${APP_C})
  target_include_directories(${TARGET} PUBLIC "${TARGET}/")
  target_link_libraries(${TARGET} engine shapeFactory)
endfunction()

# cd build/ && make 00_BasicApp && cd ../bin && ./00_BasicApp
add_target(00_BasicApp)

# cd build/ && make 01_Cube && cd ../bin && ./01_Cube
add_target(01_Cube)

# cd build/ && make 02_Sierpinski && cd ../bin && ./02_Sierpinski
add_target(02_Sierpinski)

# cd build/ && make 03_Shapes2D && cd ../bin && ./03_Shapes2D
add_target(03_Shapes2D)

# cd build/ && make 04_Maze && cd ../bin && ./04_Maze
add_target(04_Maze)

# cd build/ && make 05_GenArt && cd ../bin && ./05_GenArt
add_target(05_GenArt)

# cd build/ && make 06_Maxwell && cd ../bin && ./06_Maxwell
add_target(06_Maxwell)

# cd build/ && make 07_Bounce && cd ../bin && ./07_Bounce
add_target(07_Bounce)

# cd build/ && make 08_Pixels && cd ../bin && ./08_Pixels
add_target(08_Pixels)
