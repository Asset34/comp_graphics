#include "window.h"

#include "glrenderer.h"
#include "ui/glfwimguicameramanager.h"

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

    // Setup scene
    // m_scene = new SceneLR1;
    m_scene = nullptr;

    // Setup renderer
    m_renderer = new GLRenderer;
    m_renderer->init();
    // m_renderer->attach(m_scene);

    // Setup UI Manager
    // m_uiManager.init(m_window);
    // m_uiManager = nullptr;
    m_uiManager = new GlfwImguiCameraManager(m_window);
}

Window::~Window()
{
    glfwTerminate();

    if (m_scene) delete m_scene;
    if (m_renderer) delete m_renderer;
    if (m_uiManager) delete m_uiManager;
}

UiManager *Window::getCurrentUiManager() const
{
    return m_uiManager;
}

void Window::draw()
{
    while (!shouldClose()) {
        glfwPollEvents();

        if (m_scene) m_scene->update();
        if (m_renderer) m_renderer->render();
        if (m_uiManager) m_uiManager->render();

        glfwSwapBuffers(m_window);
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}