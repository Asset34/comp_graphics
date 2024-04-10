#ifndef WINDOW_H_H
#define WINDOW_H_H

#include <string>
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "abstract/scene.h"
#include "abstract/renderer.h"

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    void draw();
    bool shouldClose() const;

private:
    // Event handlers
    // static void resizeEvent(GLFWwindow* window, int width, int height);
    // static void mouseMovementEvent(GLFWwindow* window, double xpos, double ypos);
    // static void museScrollEvent(GLFWwindow* window, double xoffset, double yoffset);
    
    GLFWwindow* m_window;
    std::string m_title;
    int m_width, m_height;

    Renderer *m_renderer;
    Scene *m_scene;

    // bool m_mouseFirstClick;
    // float m_mouseLastx, m_mouseLasty;
    // float m_mouseSensitivity;

};

#endif // WINDOW_H_H