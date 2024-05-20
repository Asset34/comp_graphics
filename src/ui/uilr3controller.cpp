#include "ui/uilr3controller.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

UiLr3Controller::UiLr3Controller(GLFWwindow * w, bool manageContext)
    : UiSceneController3D(w, manageContext)
{
}

void UiLr3Controller::initFromControllable()
{
}

void UiLr3Controller::updateFromControllable()
{
}

void UiLr3Controller::control()
{
}

void UiLr3Controller::renderUi()
{
    UiSceneController3D::renderUi();

    ImGui::Begin("Control Points");

    ImGui::SeparatorText("Polygon Net");
    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
    for (int i = 0; i < m_rowSize; i++) {
        for (int j = 0; j < m_columnSize; j++) {
            char buf[32];
            sprintf(buf, "B(%d,%d)", i, j);

            if (j > 0) ImGui::SameLine();

            if(ImGui::Selectable(buf, (i == m_selectedRow) && (j == m_selectedColumn), 0, ImVec2(50, 50))) {
                m_selectedRow = i;
                m_selectedColumn = j;

                m_pointSelectedChanged = false;
            }
        }
    }
    ImGui::PopStyleVar();

    ImGui::SeparatorText("Point Edit");
    m_pointChanged |= ImGui::SliderFloat("x", &m_point[0], -100.0, 100.0);
    m_pointChanged |= ImGui::SliderFloat("y", &m_point[1], -100.0, 100.0);
    m_pointChanged |= ImGui::SliderFloat("z", &m_point[2], -100.0, 100.0);


    ImGui::End();
}
