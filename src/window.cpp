#include "window.h"

#include "glrenderer.h"
#include "ui/lr1controller.h"
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
    scene->getObservationController()->setAspectRatio((float) width / height);

    GLRenderer *renderer = new GLRenderer;
    renderer->init();
    renderer->attach(scene);

    Lr1Controller *uiManager = new Lr1Controller(m_window);
    uiManager->attachControllable(scene);
    uiManager->attachObservationController(scene->getObservationController());

    m_workspace.attach(scene, renderer, uiManager);
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