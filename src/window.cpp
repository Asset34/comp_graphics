#include "window.h"

#include "glrenderer.h"
#include "ui/uilr1controller.h"
#include "scenes/scenelr1.h"
#include "glrenderer.h"

#include "scenes/scenetest2d.h"
#include "ui/uitestcontroller2d.h"

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
    this->setupMainUiController();
    this->setupWorkspaces();
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
    SceneLR1 *scene1 = new SceneLR1;
    GLRenderer *renderer1 = new GLRenderer;
    renderer1->attach(scene1);
    UiLr1Controller *uiManager1 = new UiLr1Controller(m_window);
    // uiManager1->setAreaMargins(0, 200, 0, 0);
    uiManager1->attachControllable(scene1);
    uiManager1->attachObservationController(scene1->getObservationController());
    uiManager1->handlePostRendering();


    // Setup 2D test workspace
    SceneTest2D *scene2 = new SceneTest2D;
    GLRenderer *renderer2 = new GLRenderer;
    renderer2->attach(scene2);
    UiTestController2D *uiManager2 = new UiTestController2D(m_window);
    uiManager2->attachControllable(scene2);
    uiManager2->attachObservationController(scene2->getObservationController());
    uiManager2->handlePostRendering();


    // Setup Additional 3D Space
    SceneLR1 *scene3 = new SceneLR1;
    GLRenderer *renderer3 = new GLRenderer;
    renderer3->attach(scene3);
    UiLr1Controller *uiManager3 = new UiLr1Controller(m_window);
    // uiManager1->setAreaMargins(0, 200, 0, 0);
    uiManager3->attachControllable(scene3);
    uiManager3->attachObservationController(scene3->getObservationController());
    uiManager3->handlePostRendering();


    // Add workspaces to the vector
    m_workspaces.resize(3);
    m_workspaces[0].attach(scene1, renderer1, uiManager1);
    m_workspaces[1].attach(scene2, renderer2, uiManager2);
    m_workspaces[2].attach(scene3, renderer3, uiManager3);

    // Setup initial workspace
    m_currentWorkspaceIndex = 0;
    m_currentWorkspace = &m_workspaces[0];
}
