#ifndef WINDOW_H_H
#define WINDOW_H_H

#include <string>

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "renderer.h"

class Window {

private:
    Renderer renderer;
    GLFWwindow* window;

    std::string title;
    int width, height;

public:
    Window(std::string title, int width, int height);
    ~Window();

    bool open();
    void close();

    void draw();
    bool shouldClose() const;

};

#endif // WINDOW_H_H