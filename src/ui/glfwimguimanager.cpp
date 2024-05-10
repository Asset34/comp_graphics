#include "window.h"
#include "ui/glfwimguimanager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_impl_glfw.h"

GlfwImguiManager::GlfwImguiManager(GLFWwindow *w)
    : m_window(w)
{
    if (m_window) {
        this->init();
    }

    // Setup Callbacks
    glfwSetFramebufferSizeCallback(m_window, onWindowResizeEvent);
    glfwSetCursorPosCallback(m_window, onMouseMovementEvent);
    glfwSetScrollCallback(m_window, onMouseScrollEvent);
    glfwSetKeyCallback(m_window, onKeyEvent);
}

GlfwImguiManager::~GlfwImguiManager()
{
    this->destroy();
}

void GlfwImguiManager::manage()
{
    this->render();
}

void GlfwImguiManager::init(GLFWwindow *w)
{
    if (m_window) {
        this->destroy();
        m_window = w;
    }

    if (m_window) this->init();
}

void GlfwImguiManager::render()
{
    this->renderBegin();
    ImGui::ShowDemoWindow();
    this->renderEnd();
}

void GlfwImguiManager::renderBegin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void GlfwImguiManager::renderEnd()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

GLFWwindow *GlfwImguiManager::getWindowPtr() const
{
    return m_window;
}

void GlfwImguiManager::init()
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();
}

void GlfwImguiManager::destroy()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
