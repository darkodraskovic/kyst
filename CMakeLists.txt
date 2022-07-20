cmake_minimum_required(VERSION 3.8)
project(kyst)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

if (WIN32)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_CURRENT_SOURCE_DIR}/bin")
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_CURRENT_SOURCE_DIR}/bin")

  include_directories(lib/ lib/glad/include lib/glm lib/glfw/include)

  link_directories(lib/glfw/lib-vc2019)
  link_libraries(glfw3.lib)

  set(warning_compiler_options /W3 /wd"4267" /wd"4305" /wd"4244")
  add_compile_options(${warning_compiler_options} /MD /JMC)
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

add_target(00_BasicApp)
add_target(01_Cube)
add_target(02_Sierpinski)
add_target(03_Shapes2D)
add_target(04_Maze)
add_target(05_GenArt)
add_target(06_Maxwell)
add_target(07_Bounce)
add_target(08_Pixels)
