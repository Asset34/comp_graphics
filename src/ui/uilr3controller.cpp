#include "ui/uilr3controller.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>

#include <iostream>

UiLr3Controller::UiLr3Controller(GLFWwindow * w, bool manageContext)
    : UiSceneController3D(w, manageContext),
      m_surfaceHeightChanged(false),
      m_surfaceWidthChanged(false),
      m_surfaceColumnValueChanged(false),
      m_surfaceRowValueChanged(false),
      m_controlPointValueChanged(false)
{
    m_surfaceColumn = 0;
    m_surfaceRow = 0;
}

void UiLr3Controller::initFromControllable()
{
    // Init Surace Polygon

    this->getControllable()->get(VID_SURFACE_HEIGHT, m_surfaceHeight);
    this->getControllable()->get(VID_SURFACE_WIDTH, m_surfaceWidth);
    m_surfaceValues.resize(m_surfaceHeight);

    m_surfaceRowValues.resize(m_surfaceHeight);
    for (int i = 0; i < m_surfaceHeight; i++) {
        this->getControllable()->set(VID_SURFACE_ROW, i);
        this->getControllable()->get(VID_SURFACE_ROW_VALUE, m_surfaceRowValues[i]);
    }
    m_surfaceColumnValues.resize(m_surfaceWidth);
    for (int j = 0; j < m_surfaceWidth; j++) {
        this->getControllable()->set(VID_SURFACE_COLUMN, j);
        this->getControllable()->get(VID_SURFACE_COLUMN_VALUE, m_surfaceColumnValues[j]);
    }

    for (int i = 0; i < m_surfaceHeight; i++) {
        this->getControllable()->set(VID_SURFACE_ROW, i);
        m_surfaceValues[i].resize(m_surfaceWidth);
        for (int j = 0; j < m_surfaceWidth; j++) {
            this->getControllable()->set(VID_SURFACE_COLUMN, j);
            this->getControllable()->get(VID_SURFACE_VALUE, m_surfaceValues[i][j]);
        }
    }
}

void UiLr3Controller::updateFromControllable()
{
    if (!this->getControllable()->updated()) return;

    for (auto i : this->getControllable()->getUpdateList()) {
        switch(i)
        {
        case VID_SURFACE_VALUE:
            for (int i = 0; i < m_surfaceHeight; i++) {
                this->getControllable()->set(VID_SURFACE_ROW, i);
                // m_surfaceValues[i].resize(m_surfaceWidth);
                for (int j = 0; j < m_surfaceWidth; j++) {
                    this->getControllable()->set(VID_SURFACE_COLUMN, j);
                    this->getControllable()->get(VID_SURFACE_VALUE, m_surfaceValues[i][j]);
                }
            }
        break;
        case VID_SURFACE_ROW_VALUE:
            for (int i = 0; i < m_surfaceHeight; i++) {
                this->getControllable()->set(VID_SURFACE_ROW, i);
                this->getControllable()->get(VID_SURFACE_ROW_VALUE, m_surfaceRowValues[i]);
            }
        break;
        case VID_SURFACE_COLUMN_VALUE:
            for (int j = 0; j < m_surfaceWidth; j++) {
                this->getControllable()->set(VID_SURFACE_COLUMN, j);
                this->getControllable()->get(VID_SURFACE_COLUMN_VALUE, m_surfaceColumnValues[j]);
            }
        break;
        }
    }

    this->getControllable()->updateAck();
}

void UiLr3Controller::control()
{
    if (m_surfaceHeightChanged) {
        this->getControllable()->set(VID_SURFACE_HEIGHT, m_surfaceHeight);
        this->getControllable()->control(CMD_SET_SURFACE_HEIGHT);

        // Update UI
        m_surfaceRowValues.resize(m_surfaceHeight);
        m_surfaceValues.resize(m_surfaceHeight);
        for (auto &row : m_surfaceValues) {
            row.resize(m_surfaceWidth);
        }

        m_surfaceHeightChanged = false;
    }

    if (m_surfaceWidthChanged) {
        this->getControllable()->set(VID_SURFACE_WIDTH, m_surfaceWidth);
        this->getControllable()->control(CMD_SET_SURFACE_WIDTH);

        // Update UI
        m_surfaceColumnValues.resize(m_surfaceWidth);
        for (auto &row : m_surfaceValues) {
            row.resize(m_surfaceWidth);
        }

        m_surfaceWidthChanged = false;
    }

    if (m_surfaceRowValueChanged) {
        this->getControllable()->set(VID_SURFACE_ROW, m_surfaceRow);
        this->getControllable()->set(VID_SURFACE_ROW_VALUE, m_surfaceRowValues[m_surfaceRow]);
        this->getControllable()->control(CMD_SET_SURFACE_ROW_VALUE);

        m_surfaceRowValueChanged = false;
    }

    if (m_surfaceColumnValueChanged) {
        this->getControllable()->set(VID_SURFACE_COLUMN, m_surfaceColumn);
        this->getControllable()->set(VID_SURFACE_COLUMN_VALUE, m_surfaceColumnValues[m_surfaceColumn]);
        this->getControllable()->control(CMD_SET_SURFACE_COLUMN_VALUE);

        m_surfaceColumnValueChanged = false;
    }

    if (m_controlPointValueChanged) {
        this->getControllable()->set(VID_SURFACE_ROW, m_surfaceRow);
        this->getControllable()->set(VID_SURFACE_COLUMN, m_surfaceColumn);
        this->getControllable()->set(VID_SURFACE_VALUE, m_surfaceValues[m_surfaceRow][m_surfaceColumn]);
        this->getControllable()->control(CMD_SET_SURFACE_VALUE);

        m_controlPointValueChanged = false;
    }
}

void UiLr3Controller::renderUi()
{
    // UiSceneController3D::renderUi();

    ImGui::Begin("Control Points");

    ImGui::SeparatorText("Polygon");
    
    ImGui::PushItemWidth(100);
    
    m_surfaceHeightChanged = ImGui::InputInt("H", &m_surfaceHeight);
    if (m_surfaceHeight < 1) m_surfaceHeight = 1;
    ImGui::SameLine();
    m_surfaceWidthChanged = ImGui::InputInt("W", &m_surfaceWidth);
    if (m_surfaceWidth < 1) m_surfaceWidth = 1;

    ImGui::PopItemWidth();

    ImGui::PushStyleVar(ImGuiStyleVar_SelectableTextAlign, ImVec2(0.5f, 0.5f));
    for (int i = 0; i < m_surfaceValues.size(); i++) {
        for (int j = 0; j < m_surfaceValues[0].size(); j++) {
            if (j > 0) ImGui::SameLine();

            char buf[32];
            sprintf(buf, "%.2f\n%.2f\n%.2f##%d%d", m_surfaceColumnValues[j], m_surfaceRowValues[i], m_surfaceValues[i][j], i, j);
            if (ImGui::Selectable(buf, (i == m_surfaceRow) && (j == m_surfaceColumn), 0, ImVec2(50, 50))) {
                m_surfaceRow = i;
                m_surfaceColumn = j;
            }
        }
    }
    ImGui::PopStyleVar();


    ImGui::SeparatorText("Control Point");

    float min, max;
    
    min = -100;
    if (m_surfaceColumn) min = m_surfaceColumnValues[m_surfaceColumn - 1];
    max = 100;
    if (m_surfaceColumn < m_surfaceWidth - 1) max = m_surfaceColumnValues[m_surfaceColumn + 1];

    m_surfaceColumnValueChanged =  ImGui::SliderFloat("x", &m_surfaceColumnValues[m_surfaceColumn], min, max);

    min = -100;
    if (m_surfaceRow) min = m_surfaceRowValues[m_surfaceRow - 1];
    max = 100;
    if (m_surfaceRow < m_surfaceHeight - 1) max = m_surfaceRowValues[m_surfaceRow + 1];
    m_surfaceRowValueChanged = ImGui::SliderFloat("y", &m_surfaceRowValues[m_surfaceRow], min, max);


    m_controlPointValueChanged = ImGui::SliderFloat("z", &m_surfaceValues[m_surfaceRow][m_surfaceColumn], -100, 100);

    ImGui::End();
}
