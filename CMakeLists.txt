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
elseif(UNIX)
    set(LIB_PLATFORM "linux")
endif()

# Import GLFW library
add_library(libglfw3 STATIC IMPORTED)
set_property(TARGET libglfw3 PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PROJECT_SOURCE_DIR}/${INCLUDE}/${INCLUDE_LIB})
set_property(TARGET libglfw3 PROPERTY IMPORTED_LOCATION ${PROJECT_SOURCE_DIR}/${LIB}/${LIB_PLATFORM}/libglfw3.a)

# Define GLAD as object library
add_library(glad OBJECT
    ${SRC}/${LIB}/glad/glad.c
)
target_include_directories(glad PUBLIC ${INCLUDE}/${INCLUDE_LIB})

# Define ImGui as object library
add_library(imgui OBJECT
    ${SRC}/${LIB}/imgui/imgui.cpp
    ${SRC}/${LIB}/imgui/imgui_tables.cpp
    ${SRC}/${LIB}/imgui/imgui_widgets.cpp
    ${SRC}/${LIB}/imgui/imgui_draw.cpp
    ${SRC}/${LIB}/imgui/imgui_demo.cpp
    ${SRC}/${LIB}/imgui/imgui_impl_opengl3.cpp
    ${SRC}/${LIB}/imgui/imgui_impl_glfw.cpp
    )
target_include_directories(imgui PUBLIC ${INCLUDE}/${INCLUDE_LIB})
target_include_directories(imgui PUBLIC ${INCLUDE}/${INCLUDE_LIB}/imgui)

# Create executavle
add_executable(project
    ${SRC}/abstract/renderer.cpp
    ${SRC}/abstract/transformableobj.cpp
    ${SRC}/glrenderer.cpp
    ${SRC}/glrendererunit.cpp
    ${SRC}/ui/glfwimguimanager.cpp
    ${SRC}/ui/uicontroller.cpp
    ${SRC}/ui/uiscenecontroller.cpp
    ${SRC}/ui/uiscenecontroller3d.cpp
    ${SRC}/ui/lr1controller.cpp
    ${SRC}/scenes/scene3d.cpp
    ${SRC}/scenes/scenelr1.cpp
    ${SRC}/objects/shape.cpp
    ${SRC}/objects/line.cpp
    ${SRC}/workspace.cpp
    ${SRC}/shader.cpp
    ${SRC}/camera3d.cpp
    ${SRC}/window.cpp
    ${SRC}/main.cpp
    $<TARGET_OBJECTS:glad>
    $<TARGET_OBJECTS:imgui>
)
set_target_properties(project PROPERTIES CXX_STANDARD 11)
target_link_libraries(project libglfw3)
target_include_directories(project PUBLIC ${INCLUDE})
target_include_directories(project PUBLIC ${INCLUDE}/${INCLUDE_LIB})