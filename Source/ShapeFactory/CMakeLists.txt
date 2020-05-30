file(GLOB SHAPE_FACTORY_C "*.cpp")

add_library(shapeFactory SHARED ${SHAPE_FACTORY_C})
target_include_directories(shapeFactory PUBLIC ".")
target_link_libraries(shapeFactory PRIVATE engine)
