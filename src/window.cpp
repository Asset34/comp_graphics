#include "window.h"

Window::Window(std::string title, int width, int height)
    :title(title), width(width), height(height)
{
}

Window::~Window()
{
    close();
}

bool Window::open()
{
    // Init OPENGL context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(window);

    return true;
}

void Window::close()
{
    glfwTerminate();
}

void Window::draw()
{
    // Init renderer
    renderer.init();
    
    while (!shouldClose()) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}
