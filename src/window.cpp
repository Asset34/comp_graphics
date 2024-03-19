#include "window.h"

Window::Window(std::string title, int width, int height)
    :m_title(title), m_width(width), m_height(height)
    
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

    // Setup renderer
    m_renderer.init();
    m_renderer.attachScene(m_scene);
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

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}