#ifndef WINDOW_H_H
#define WINDOW_H_H

#include <string>

#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "renderer.h"
#include "scene.h"

class Window {

private:
    Renderer m_renderer;
    Scene m_scene;
    GLFWwindow* m_window;

    std::string m_title;
    int m_width, m_height;

public:
    Window(std::string title, int width, int height);
    ~Window();

    void draw();
    bool shouldClose() const;

};

#endif // WINDOW_H_H