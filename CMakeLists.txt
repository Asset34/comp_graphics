cmake_minimum_required(VERSION 3.10)
project(OpenGL_test LANGUAGES C CXX)

# Project variables
set(INCLUDE "include")
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
set_property(TARGET libglfw3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/${INCLUDE})
set_property(TARGET libglfw3 PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/${LIB}/${LIB_PLATFORM}/libglfw3.a)

# Define GLAD as object library
add_library(glad OBJECT ${SRC}/glad.c)
target_include_directories(glad PUBLIC ${INCLUDE})

add_executable(test
    ${SRC}/main.cpp
    $<TARGET_OBJECTS:glad>
)

set_target_properties(test PROPERTIES CXX_STANDARD 11)
target_link_libraries(test libglfw3)