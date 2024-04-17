#include "window.h"

#include "glrenderer.h"
#include "ui/lr1uimanager.h"
#include "scenes/scenelr1.h"
#include "glrenderer.h"

Window::Window(const std::string &title, int width, int height)
    :m_title(title),
     m_width(width),
     m_height(height)
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

    // Setup workspace

    SceneLR1 *scene = new SceneLR1;
    scene->getCameraController()->setAspectRatio((float) width / height);

    GLRenderer *renderer = new GLRenderer;
    renderer->init();
    renderer->attach(scene);

    LR1UiManager *manager = new LR1UiManager(m_window);
    manager->attachController(scene->getCameraController());
    manager->attachControllable(scene);

    m_workspace.attach(scene, renderer, manager);
}

Window::~Window()
{
    glfwTerminate();
}

UiManager *Window::getCurrentUiManager() const
{
    return m_workspace.getUiManager();
}

void Window::draw()
{
    while (!shouldClose()) {
        glfwPollEvents();
        m_workspace.run();
        glfwSwapBuffers(m_window);
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}