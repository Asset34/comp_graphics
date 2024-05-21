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
      m_controlPointValueChanged(false),
      m_hknotChanged(false),
      m_wknotChanged(false),
      m_hrenderStepChanged(false),
      m_wrenderStepChanged(false)
{
    m_surfaceColumn = 0;
    m_surfaceRow = 0;
    m_hknotStep = 1.0;
    m_wknotStep = 1.0;
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

    // Init knots

    int size;
    this->getControllable()->get(VID_HKNOT_SIZE, size);
    float hknotsValues[size];
    this->getControllable()->get(VID_HKNOTS, hknotsValues);
    m_hknots.resize(size);
    for (int i = 0; i < m_hknots.size(); i++) {
        m_hknots[i] = hknotsValues[i];
    }

    this->getControllable()->get(VID_WKNOT_SIZE, size);
    float wknotsValues[size];
    this->getControllable()->get(VID_WKNOTS, wknotsValues);
    m_wknots.resize(size);
    for (int i = 0; i < m_wknots.size(); i++) {
        m_wknots[i] = wknotsValues[i];
    }

    // Init degrees
    this->getControllable()->get(VID_HDEGREE_VALUE, m_hdegree);
    this->getControllable()->get(VID_HDEGREE_MAX, m_hdegreeMax);
    this->getControllable()->get(VID_WDEGREE_VALUE, m_wdegree);
    this->getControllable()->get(VID_WDEGREE_MAX, m_wdegreeMax);

    // Init render steps
    this->getControllable()->get(VID_HSTEP, m_hrenderStep);
    this->getControllable()->get(VID_WSTEP, m_wrenderStep);
}

void UiLr3Controller::updateFromControllable()
{
    if (!this->getControllable()->updated()) return;

    int size;

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
        case VID_HKNOTS:
        {
            this->getControllable()->get(VID_HKNOT_SIZE, size);
            float knotsValues[size];
            this->getControllable()->get(VID_HKNOTS, knotsValues);
            m_hknots.resize(size);
            for (int i = 0; i < m_hknots.size(); i++) {
                m_hknots[i] = knotsValues[i];
            }
        }
        case VID_WKNOTS:
        {
            this->getControllable()->get(VID_WKNOT_SIZE, size);
            float knotsValues[size];
            this->getControllable()->get(VID_WKNOTS, knotsValues);
            m_wknots.resize(size);
            for (int i = 0; i < m_wknots.size(); i++) {
                m_wknots[i] = knotsValues[i];
            }
        }
        break;
        case VID_HDEGREE_MAX:
            this->getControllable()->get(VID_HDEGREE_MAX, m_hdegreeMax);
        break;
        case VID_HDEGREE_VALUE:
            this->getControllable()->get(VID_HDEGREE_VALUE, m_hdegree);
        break;
        case VID_WDEGREE_MAX:
            this->getControllable()->get(VID_WDEGREE_MAX, m_wdegreeMax);
        break;
        case VID_WDEGREE_VALUE:
            this->getControllable()->get(VID_WDEGREE_VALUE, m_wdegree);
        break;
        case VID_HSTEP:
            this->getControllable()->get(VID_HSTEP, m_hrenderStep);
        break;
        case VID_WSTEP:
            this->getControllable()->get(VID_WSTEP, m_wrenderStep);
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

    if (m_hknotChanged) {
        this->getControllable()->set(VID_KNOT_INDEX, m_hknotIndex);
        this->getControllable()->set(VID_KNOT_VALUE, m_hknots[m_hknotIndex]);
        this->getControllable()->control(CMD_HKNOT_SET);

        m_hknotChanged = false;
    }

    if (m_wknotChanged) {
        this->getControllable()->set(VID_KNOT_INDEX, m_wknotIndex);
        this->getControllable()->set(VID_KNOT_VALUE, m_wknots[m_wknotIndex]);
        this->getControllable()->control(CMD_WKNOT_SET);

        m_hknotChanged = false;
    }

    if (m_buttonUniformHKnots) {
        this->getControllable()->set(VID_KNOT_STEP, m_hknotStep);
        this->getControllable()->control(CMD_HKNOTS_UNIFORM);

        m_buttonUniformHKnots = false;
    }
    if (m_buttonUniformWKnots) {
        this->getControllable()->set(VID_KNOT_STEP, m_wknotStep);
        this->getControllable()->control(CMD_WKNOTS_UNIFORM);

        m_buttonUniformWKnots = false;
    }
    if (m_buttonOpenUniformHKnots) {
        this->getControllable()->set(VID_KNOT_STEP, m_hknotStep);
        this->getControllable()->control(CMD_HKNOTS_OPENUNIFORM);

        m_buttonOpenUniformHKnots = false;
    }
    if (m_buttonOpenUniformWKnots) {
        this->getControllable()->set(VID_KNOT_STEP, m_wknotStep);
        this->getControllable()->control(CMD_WKNOTS_OPENUNIFORM);

        m_buttonOpenUniformHKnots = false;
    }

    if (m_hrenderStepChanged) {
        this->getControllable()->set(VID_HSTEP, m_hrenderStep);
        this->getControllable()->control(CMD_HSTEP_SET);

        m_hrenderStepChanged = false;
    }

    if (m_wrenderStepChanged) {
        this->getControllable()->set(VID_WSTEP, m_wrenderStep);
        this->getControllable()->control(CMD_WSTEP_SET);

        m_wrenderStepChanged = false;
    }
}

void UiLr3Controller::renderUi()
{
    // UiSceneController3D::renderUi();

    ImGui::Begin("Surface Control");

    // ImGui::BeginGroup()
    ImGui::SeparatorText("Control Points Mesh");


    ImGui::BeginGroup();
        ImGui::PushItemWidth(100);
        m_surfaceHeightChanged = ImGui::InputInt("H", &m_surfaceHeight);
        if (m_surfaceHeight < 1) m_surfaceHeight = 1;
        ImGui::SameLine();
        m_surfaceWidthChanged = ImGui::InputInt("W", &m_surfaceWidth);
        if (m_surfaceWidth < 1) m_surfaceWidth = 1;
        ImGui::PopItemWidth();

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

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
    ImGui::EndGroup();

    ImGui::Separator();
    // ImGui::SameLine();

    ImGui::BeginGroup();
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
    ImGui::EndGroup();

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Spacing();

    if (ImGui::BeginTabBar("MyTabBar"))
    {
        if (ImGui::BeginTabItem("Height"))
        {
            ImGui::SeparatorText("Degree");
            ImGui::SliderInt("Degree##Height", &m_hdegree, 1, m_hdegreeMax);

            ImGui::SeparatorText("Knots");
            ImGui::PushItemWidth(120);
            m_buttonUniformHKnots = ImGui::Button("Uniform##Height");
            ImGui::SameLine();
            m_buttonOpenUniformHKnots = ImGui::Button("Open Uniform##Height");
            ImGui::SameLine();
            ImGui::InputFloat("Step##Height", &m_hknotStep, 0.1);
            if (m_hknotStep < 0) {
                m_hknotStep = 0;
            }
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::Spacing();
            
            for (int i = 0; i < m_hknots.size(); i++) {
                char buf[32];
                sprintf(buf, "x%d", i);

                if (!m_hknotChanged) {
                    m_hknotIndex = i;
                }

                // Determine min for current knot        
                if (i == 0) {
                    min = 0;
                } else {
                    min = m_hknots[i - 1];
                }

                // Determine max for current knot        
                if (i + 1 == m_hknots.size()) {
                    max = 20;
                } else {
                    max = m_hknots[i + 1];
                }

                m_hknotChanged |= ImGui::SliderFloat(buf, &m_hknots[i], min, max);

                // Check for borders
                if (m_hknots[i] < min) m_hknots[i] = min;
                if (m_hknots[i] > max) m_hknots[i] = max;
            }

            ImGui::SeparatorText("Render");
            m_hrenderStepChanged = ImGui::SliderFloat("Step##HRender", &m_hrenderStep, 0.01, 1.0, "%.3f", ImGuiSliderFlags_Logarithmic);

            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Width"))
        {
            ImGui::SeparatorText("Degree");
            ImGui::SliderInt("Degree##Width", &m_wdegree, 1, m_wdegreeMax);

            ImGui::SeparatorText("Knots");
            ImGui::PushItemWidth(120);
            m_buttonUniformWKnots = ImGui::Button("Uniform##Width");
            ImGui::SameLine();
            m_buttonOpenUniformWKnots = ImGui::Button("Open Uniform##Width");
            ImGui::SameLine();
            ImGui::InputFloat("Step##Width", &m_wknotStep, 0.1);
            if (m_wknotStep < 0) {
                m_wknotStep = 0;
            }
            ImGui::PopItemWidth();

            ImGui::Spacing();
            ImGui::Spacing();
            
            for (int i = 0; i < m_wknots.size(); i++) {
                char buf[32];
                sprintf(buf, "x%d", i);

                if (!m_hknotChanged) {
                    m_hknotIndex = i;
                }

                // Determine min for current knot        
                if (i == 0) {
                    min = 0;
                } else {
                    min = m_wknots[i - 1];
                }

                // Determine max for current knot        
                if (i + 1 == m_wknots.size()) {
                    max = 20;
                } else {
                    max = m_wknots[i + 1];
                }

                m_hknotChanged |= ImGui::SliderFloat(buf, &m_wknots[i], min, max);

                // Check for borders
                if (m_wknots[i] < min) m_wknots[i] = min;
                if (m_wknots[i] > max) m_wknots[i] = max;
            }

            ImGui::SeparatorText("Render");
            m_wrenderStepChanged = ImGui::SliderFloat("Step##WRender", &m_wrenderStep, 0.001, 1.0, "%.3f", ImGuiSliderFlags_Logarithmic);

            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }

    ImGui::End();
}
