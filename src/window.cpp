#include "window.h"

#include <iostream>
#include "scenes/scenelr1.h"
#include "glrenderer.h"

Window::Window(const std::string &title, int width, int height)
    :m_title(title),
     m_width(width),
     m_height(height)
    //  m_mouseFirstClick(true),
    //  m_mouseSensitivity(1.0f)
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
    // glfwSetFramebufferSizeCallback(m_window, resizeEvent);
    // glfwSetCursorPosCallback(m_window, mouseMovementEvent);
    // glfwSetScrollCallback(m_window, museScrollEvent);

    // TODO: Setup scene
    m_scene = new SceneLR1;

    // TODO: Setup renderer
    m_renderer = new GLRenderer;
    m_renderer->init();
    m_renderer->attach(m_scene);
}

Window::~Window()
{
    glfwTerminate();

    if (m_scene) delete m_scene;
    if (m_renderer) delete m_renderer;
}

void Window::draw()
{
    while (!shouldClose()) {
        glfwPollEvents();

        if (m_scene) m_scene->update();
        if (m_renderer) m_renderer->render();

        glfwSwapBuffers(m_window);
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

// void Window::resizeEvent(GLFWwindow *window, int width, int height)
// {
//     Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

//     w->m_scene.setCameraAspectRatio((float) width / height);
//     glViewport(0, 0, width, height);
// }

// void Window::mouseMovementEvent(GLFWwindow *window, double xpos, double ypos)
// {
//     Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

//     int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);
//     if (state == GLFW_PRESS)
//     {
//         if (w->m_mouseFirstClick) {
//             w->m_mouseLastx = xpos;
//             w->m_mouseLasty = ypos;

//             w->m_mouseFirstClick = false;
//         }

//         float offsetx = (xpos - w->m_mouseLastx) * w->m_mouseSensitivity;
//         float offsety = (ypos - w->m_mouseLasty) * w->m_mouseSensitivity;
        
//         w->m_mouseLastx = xpos;
//         w->m_mouseLasty = ypos;

//         w->m_scene.cameraRotateYaw(-offsetx);
//         w->m_scene.cameraRotatePitch(-offsety);
        
//     } else {
//         w->m_mouseFirstClick = true;
//     }
// }

// void Window::museScrollEvent(GLFWwindow *window, double xoffset, double yoffset)
// {
//     // std::cout << yoffset << std::endl;
//     Window *w = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window));

//     if (yoffset > 0) {
//         w->m_scene.cameraZoomIn();

//     } else {
//         w->m_scene.cameraZoomOut();
//     }
// }
