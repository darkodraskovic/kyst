set(SAMPLES "Source/Samples")

function(add_target TARGET)
  file(GLOB APP_C "${SAMPLES}/${TARGET}/*.cpp")
  add_executable(${TARGET} ${APP_C})
  target_include_directories(${TARGET} PUBLIC "${SAMPLES}/${TARGET}/")
  target_link_libraries(${TARGET} GL GLU glfw dl engine shapeFactory)
endfunction()
