#include "window.h"
#include "ui/uiwindowcontroller.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

UiWindowController::UiWindowController(GLFWwindow *w, bool manageContext)
    : GlfwImguiManager(w, manageContext),
      m_window(nullptr),
      m_changed(false)
{
}

UiWindowController::~UiWindowController()
{
}

void UiWindowController::attach(Window *w)
{
    m_window = w;
    this->initFrom();
}

void UiWindowController::manage() 
{
    if (!m_window) {
        return;
    }

    // this->updateFrom();
    this->render();
    this->control();
}

void UiWindowController::renderUi()
{
    ImGui::Begin("Workspaces");

    for (int i = 0; i < m_workspacesNumber; i++)
    {
        if (ImGui::Selectable(m_workspacesNames[i].c_str(), m_workspaceSelected == i)) {
            m_workspaceSelected = i;
            m_changed = true;
        }
    }

    ImGui::End();
}

void UiWindowController::initFrom()
{
    this->updateFrom();
}

void UiWindowController::control() 
{
    if(!m_window) {
        return;
    }

    if (m_changed) {
        m_window->setCurrentWorkspace(m_workspaceSelected);

        m_changed = false;
    }
}

void UiWindowController::updateFrom()
{
    m_workspaceSelected = m_window->getCurrentWorkspaceIndex();
    m_workspacesNumber = m_window->getWorkspacesNumber();

    m_workspacesNames = m_window->getWorkspacesNames();
}