file(GLOB_RECURSE ENGINE_C "*.c" "*.cpp")
set(ENGINE_H "." "Graphics" "Scene")

add_library(engine SHARED ${ENGINE_C})
target_include_directories(engine PUBLIC ${ENGINE_H})
target_link_libraries(engine GL GLU glfw dl)
