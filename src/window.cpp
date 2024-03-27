#include "window.h"

#include <iostream>

Window::Window(std::string title, int width, int height)
    :m_title(title),
     m_width(width),
     m_height(height),
     m_mouseFirstClick(true),
     m_mouseSensitivity(1.0f)
{
    // Init OPENGL context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        glfwTerminate();
    } else {
        glfwMakeContextCurrent(m_window);
    }
    glfwSetWindowUserPointer(m_window, this);

    // Setup event handlers
    glfwSetFramebufferSizeCallback(m_window, resizeEvent);
    glfwSetCursorPosCallback(m_window, mouseMovementEvent);
    glfwSetScrollCallback(m_window, museScrollEvent);

    // Setup renderer
    m_renderer.attachScene(m_scene);
    m_renderer.init();

    // Setup scene
    m_scene.setCameraAspectRatio((float) m_width / m_height);
}

Window::~Window()
{
    glfwTerminate();
}

void Window::draw()
{
    while (!shouldClose()) {
        m_scene.update();
        m_renderer.render();

        // m_renderer.testDraw();

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

void Window::resizeEvent(GLFWwindow *window, int width, int height)
{
    Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

    w->m_scene.setCameraAspectRatio((float) width / height);
    glViewport(0, 0, width, height);
}

void Window::mouseMovementEvent(GLFWwindow *window, double xpos, double ypos)
{
    Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
    if (state == GLFW_PRESS)
    {
        if (w->m_mouseFirstClick) {
            w->m_mouseLastx = xpos;
            w->m_mouseLasty = ypos;

            w->m_mouseFirstClick = false;
        }

        float offsetx = (xpos - w->m_mouseLastx) * w->m_mouseSensitivity;
        float offsety = (ypos - w->m_mouseLasty) * w->m_mouseSensitivity;
        
        w->m_mouseLastx = xpos;
        w->m_mouseLasty = ypos;

        w->m_scene.cameraRotateYaw(-offsetx);
        w->m_scene.cameraRotatePitch(-offsety);
        
    } else {
        w->m_mouseFirstClick = true;
    }
}

void Window::museScrollEvent(GLFWwindow *window, double xoffset, double yoffset)
{
    
}
