#include "window.h"
#include "ui/glfwimguimanager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

bool GlfwImguiManager::m_contextManagerAssigned = false;
bool GlfwImguiManager::m_contextInitialized = false;
bool GlfwImguiManager::m_preRenderingHandled = false;
bool GlfwImguiManager::m_postRenderingHandled = true;
int GlfwImguiManager::m_preRenderingHandlers = 0;
int GlfwImguiManager::m_postRenderingHandlers = 0;

GlfwImguiManager::GlfwImguiManager(GLFWwindow *w, bool manageContext)
    : m_window(nullptr),
      m_manageContext(false),
      m_handlePreRendering(false),
      m_handlePostRendering(false)
{
    this->init(w, manageContext);

    // // Setup Callbacks
    // glfwSetFramebufferSizeCallback(m_window, onWindowResizeEvent);
    // glfwSetCursorPosCallback(m_window, onMouseMovementEvent);
    // glfwSetScrollCallback(m_window, onMouseScrollEvent);
    // glfwSetKeyCallback(m_window, onKeyEvent);
}

GlfwImguiManager::~GlfwImguiManager()
{
    if (m_manageContext && m_contextInitialized) {
        this->destroyContext();
    }
}

void GlfwImguiManager::manage()
{
    this->render();
}

void GlfwImguiManager::update()
{
    int windowWidth, windowHeight;
    glfwGetWindowSize(this->getWindowPtr(), &windowWidth, &windowHeight);

    this->onWindowResize(m_window, windowWidth, windowHeight);
}

void GlfwImguiManager::init(GLFWwindow *w, bool manageContext)
{
    // Destroy previous context
    if (m_manageContext && m_contextInitialized) {
        this->destroyContext();
    }

    // Init context
    m_window = w;
    m_manageContext = manageContext;
    if(m_manageContext) {
        this->initContext();
    }

    this->initLogic();
}

void GlfwImguiManager::manageContext()
{
    if (!m_contextManagerAssigned) {
        m_manageContext = true;
        m_contextManagerAssigned = true;
    }
}

void GlfwImguiManager::stopManagingContext()
{
    m_manageContext = false;
    m_contextManagerAssigned = false;
}

void GlfwImguiManager::handlePreRendering()
{
    m_handlePreRendering = true;
    m_preRenderingHandlers++;
}

void GlfwImguiManager::stopHandingPreRendering()
{
    m_handlePreRendering = false;
    m_preRenderingHandlers--;
}

void GlfwImguiManager::handlePostRendering()
{
    m_handlePostRendering = true;
    m_postRenderingHandlers++;
}

void GlfwImguiManager::stopHandingPostRendering()
{
    m_handlePostRendering = false;
    m_postRenderingHandlers--;
}

void GlfwImguiManager::render()
{
    if (!m_contextInitialized) {
        return;
    }

    // Begin
    if (m_handlePreRendering && !m_preRenderingHandled) {
        this->preRendering();
    }

    if (m_preRenderingHandled) {
        this->renderUi();
    }
    
    // End
    if (m_handlePostRendering && !m_postRenderingHandled) {
        this->postRendering();
    }
}

void GlfwImguiManager::renderUi()
{
    ImGui::ShowDemoWindow();
}

void GlfwImguiManager::initContext()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup callbacks
    glfwSetFramebufferSizeCallback(m_window, onWindowResizeEvent);
    glfwSetCursorPosCallback(m_window, onMouseMovementEvent);
    glfwSetScrollCallback(m_window, onMouseScrollEvent);
    glfwSetKeyCallback(m_window, onKeyEvent);

    m_contextInitialized = true;
}

void GlfwImguiManager::destroyContext()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    m_contextInitialized = false;
}

void GlfwImguiManager::preRendering()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    m_postRenderingHandled = false;
    m_preRenderingHandled = true;
}

void GlfwImguiManager::postRendering()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    m_postRenderingHandled = true;
    m_preRenderingHandled = false;
}

GLFWwindow *GlfwImguiManager::getWindowPtr() const
{
    return m_window;
}

void GlfwImguiManager::onWindowResizeEvent(GLFWwindow *w, int width, int height)
{
    GlfwImguiManager *current = GlfwImguiManager::retrieveThis(w);

    if (current) {
        current->onWindowResize(w, width, height);
    }
}

void GlfwImguiManager::onMouseMovementEvent(GLFWwindow *w, double xpos, double ypos)
{
    // Forward to Imgui
    ImGuiIO& io = ImGui::GetIO();
    io.AddMousePosEvent(xpos, ypos);

    // Forward to mine
    if (!io.WantCaptureMouse) {
        GlfwImguiManager *current = GlfwImguiManager::retrieveThis(w);

        if (current) {
            current->onMouseMovement(w, xpos, ypos);
        }
    }
}

void GlfwImguiManager::onMouseScrollEvent(GLFWwindow *w, double xoffset, double yoffset)
{
    // Forward to Imgui
    ImGuiIO& io = ImGui::GetIO();
    io.AddMouseWheelEvent(xoffset, yoffset);

    // Forward to mine
    if (!io.WantCaptureMouse) {
        GlfwImguiManager *current = GlfwImguiManager::retrieveThis(w);

        if (current) {
            current->onMouseScroll(w, xoffset, yoffset);
        }
    }
}

void GlfwImguiManager::onKeyEvent(GLFWwindow *w, int key, int scancode, int action, int mods)
{
    // Forward to Imgui
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplGlfw_KeyCallback(w, key, scancode, action, mods);

    // Forward to mine
    if (!io.WantCaptureKeyboard) {
        GlfwImguiManager *current = GlfwImguiManager::retrieveThis(w);

        if (current) {
            current->onKey(w, key, scancode, action, mods);
        }
    }
}

GlfwImguiManager *GlfwImguiManager::retrieveThis(GLFWwindow *w)
{
    Window *window = reinterpret_cast<Window*>(glfwGetWindowUserPointer(w));
    GlfwImguiManager *thisPtr = dynamic_cast<GlfwImguiManager*>(window->getCurrentUiManager());

    return thisPtr;
}
