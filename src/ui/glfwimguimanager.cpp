#include "ui/glfwimguimanager.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

GlfwImguiManager::GlfwImguiManager(GLFWwindow *w)
    : m_window(w)
{
    this->init();
}

GlfwImguiManager::~GlfwImguiManager()
{
    this->destroy();
}

void GlfwImguiManager::init(GLFWwindow *w)
{
    if (m_window) {
        this->destroy();
        m_window = w;
    }

    if (w) this->init();
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