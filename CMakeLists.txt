cmake_minimum_required(VERSION 3.10)
project(OpenGL_test LANGUAGES C CXX)

# Project variables
set(INCLUDE "include")
set(INCLUDE_LIB "lib")
set(SRC "src")
set(LIB "lib")

# Platform varaibles
if(WIN32)
    set(LIB_PLATFORM "windows")
elseif(LINUX)
    set(LIB_PLATFORM "linux")
endif()

# Import GLFW library
add_library(libglfw3 STATIC IMPORTED)
set_property(TARGET libglfw3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/${INCLUDE}/${INCLUDE_LIB})
set_property(TARGET libglfw3 PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/${LIB}/${LIB_PLATFORM}/libglfw3.a)

# Define GLAD as object library
add_library(glad OBJECT
    ${SRC}/glad.c
)
target_include_directories(glad PUBLIC ${INCLUDE}/${INCLUDE_LIB})

# Create executavle
add_executable(lr1
    ${SRC}/main.cpp
    ${SRC}/sceneobj.cpp
    ${SRC}/shape.cpp
    ${SRC}/shader.cpp
    ${SRC}/renderer.cpp
    ${SRC}/window.cpp
    $<TARGET_OBJECTS:glad>
)
set_target_properties(lr1 PROPERTIES CXX_STANDARD 11)
target_link_libraries(lr1 libglfw3)
target_include_directories(lr1 PUBLIC ${INCLUDE})