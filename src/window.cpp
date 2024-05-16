#include "window.h"

#include "glrenderer.h"
#include "ui/uilr1controller.h"
#include "ui/uilr2controller.h"
#include "scenes/scenelr1.h"
#include "scenes/scenelr2.h"
#include "glrenderer.h"

// #include "scenes/scenetest2d.h"
// #include "ui/uitestcontroller2d.h"

Window::Window(const std::string &title, int width, int height)
    :m_title(title),
     m_width(width),
     m_height(height),
     m_currentWorkspaceIndex(-1),
     m_currentWorkspace(nullptr)
{
    // Init OPENGL context
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    // Create GLFW window
    m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (m_window == NULL)
    {
        glfwTerminate();
    } else {
        glfwMakeContextCurrent(m_window);
    }
    glfwSetWindowUserPointer(m_window, this);

    this->initRenderer();
    this->setupWorkspaces();
    this->setupMainUiController();
}

Window::~Window()
{
    glfwTerminate();
}

UiManager *Window::getCurrentUiManager() const
{
    if (!m_currentWorkspace) {
        return nullptr;
    }

    return m_currentWorkspace->getUiManager();
}

GLFWwindow *Window::getGlfwWindow()
{
    return m_window;
}

void Window::draw()
{
    while (!shouldClose()) {
        glfwPollEvents();
        m_uiController.manage();

        if (m_currentWorkspace) {
            m_currentWorkspace->run();
        }
        
        glfwSwapBuffers(m_window);
    }
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(m_window);
}

int Window::getCurrentWorkspaceIndex() const
{
    return m_currentWorkspaceIndex;
}

std::vector<std::string> Window::getWorkspacesNames() const
{
    std::vector<std::string> names;
    names.reserve(m_workspaces.size());

    // for (auto w : m_workspaces) {
    //     names.push_back(w.getName());
    // }

    for (int i = 0; i < m_workspaces.size(); i++) {
        names.push_back(m_workspaces[i].getName());
    }

    return names;
}

int Window::getWorkspacesNumber() const
{
    return m_workspaces.size();
}

void Window::setCurrentWorkspace(int index)
{
    if (index < 0 || index >= m_workspaces.size()) {
        return;
    }

    m_currentWorkspaceIndex = index;
    m_currentWorkspace = &m_workspaces[index];
    m_currentWorkspace->update();
}

void Window::initRenderer()
{
    GLRenderer::init();
}

void Window::setupMainUiController()
{
    m_uiController.manageContext();
    m_uiController.init(m_window, true);
    m_uiController.attach(this);
    m_uiController.handlePreRendering();
}

void Window::setupWorkspaces()
{
    // Setup LR1 Workspace
    SceneLR1 *sceneLr1 = new SceneLR1;
    GLRenderer *rendererLr1 = new GLRenderer;
    rendererLr1->attach(sceneLr1);
    UiLr1Controller *uiManagerLr1 = new UiLr1Controller(m_window);
    uiManagerLr1->setAreaMargins(0, 200, 0, 0);
    uiManagerLr1->attachControllable(sceneLr1);
    uiManagerLr1->attachObservationController(sceneLr1->getObservationController());
    uiManagerLr1->handlePostRendering();

    // Setup LR2 Workspace
    SceneLR2 *sceneLr2 = new SceneLR2;
    GLRenderer *rendererLr2 = new GLRenderer;
    rendererLr2->attach(sceneLr2);
    UiLr2Controller *uiManagerLr2 = new UiLr2Controller(m_window);
    // uiManagerLr2->setAreaMargins(0, 300, 0, 0);
    uiManagerLr2->attachControllable(sceneLr2);
    uiManagerLr2->attachObservationController(sceneLr2->getObservationController());
    uiManagerLr2->handlePostRendering();

    // Setup Workspaces vector
    m_workspaces.resize(2);
    m_workspaces[0].setName("LR 1");
    m_workspaces[0].attach(sceneLr1, rendererLr1, uiManagerLr1);
    m_workspaces[1].setName("LR 2");
    m_workspaces[1].attach(sceneLr2, rendererLr2, uiManagerLr2);

    // Setup initial workspace
    m_currentWorkspaceIndex = 1;
    m_currentWorkspace = &m_workspaces[1];
}
