#include "ui/uilr2controller.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include <stdio.h>
#include <sstream>

UiLr2Controller::UiLr2Controller(GLFWwindow *w, bool manageContext)
    : UiSceneController2D(w, manageContext),
      m_controlPointChanged(false),
      m_knotChanged(false),
      m_degreeChanged(false),
      m_renderStepChanged(false),
      m_renderColorChanged(false),
      m_showControlPointsChanged(false),
      m_showControlPolygonChanged(false)
{
    m_knotStep = 1.0;
}

UiLr2Controller::~UiLr2Controller()
{
}

void UiLr2Controller::initFromControllable()
{
    // Init Control Points
    int size;
    this->getControllable()->get(VID_CONTROL_POINT_SIZE, size);
    m_controlPoints.resize(size);
    for (int i = 0; i < size; i++) {
        this->getControllable()->set(VID_CONTROL_POINT_INDEX, i);
        this->getControllable()->get(VID_CONTROL_POINT_VALUE, m_controlPoints[i].values);
    }
    
    // Init knots
    this->getControllable()->get(VID_KNOT_SIZE, size);
    float knotsValues[size];
    this->getControllable()->get(VID_KNOTS, knotsValues);
    m_knots.resize(size);
    for (int i = 0; i < m_knots.size(); i++) {
        m_knots[i] = knotsValues[i];
    }

    // Init Misc
    this->getControllable()->get(VID_DEGREE_MAX, m_degreeMax);
    this->getControllable()->get(VID_DEGREE_VALUE, m_degreeValue);
    this->getControllable()->get(VID_RENDER_STEP, m_renderStep);
    this->getControllable()->get(VID_RENDER_COLOR, m_renderColor);

    // Init Flags
    this->getControllable()->get(VID_CONTROL_POINTS_FLAG, m_showControlPoints);
    this->getControllable()->get(VID_CONTROL_POLYGON_FLAG, m_showControlPolygon);
}

void UiLr2Controller::updateFromControllable()
{
    if (!this->getControllable()->updated()) return;

    int size;

    for (auto i : this->getControllable()->getUpdateList()) {
        switch (i)
        {
        case VID_CONTROL_POINT_SIZE:
            this->getControllable()->get(VID_CONTROL_POINT_SIZE, size);
            m_controlPoints.resize(size);
        break;
        case VID_CONTROL_POINT_INDEX:
            this->getControllable()->get(VID_CONTROL_POINT_INDEX, m_controlPointIndex);
        break;
        case VID_CONTROL_POINT_VALUE:
            this->getControllable()->get(VID_CONTROL_POINT_VALUE, m_controlPoints[i].values);
        break;
        case VID_KNOTS:
        {
            this->getControllable()->get(VID_KNOT_SIZE, size);
            float knotsValues[size];
            this->getControllable()->get(VID_KNOTS, knotsValues);
            m_knots.resize(size);
            for (int i = 0; i < m_knots.size(); i++) {
                m_knots[i] = knotsValues[i];
            }
        }
        break;
        case VID_DEGREE_MAX:
            this->getControllable()->get(VID_DEGREE_MAX, m_degreeMax);
        break;
        case VID_DEGREE_VALUE:
            this->getControllable()->get(VID_DEGREE_VALUE, m_degreeValue);
        break;
        case VID_RENDER_STEP:
            this->getControllable()->get(VID_RENDER_STEP, m_renderStep);
        break;
        case VID_RENDER_COLOR:
            this->getControllable()->get(VID_RENDER_COLOR, m_renderColor);
        break;
        case VID_CONTROL_POINTS_FLAG:
            this->getControllable()->get(VID_CONTROL_POINTS_FLAG, m_showControlPoints);
        break;
        case VID_CONTROL_POLYGON_FLAG:
            this->getControllable()->get(VID_CONTROL_POLYGON_FLAG, m_showControlPolygon);
        break;
        }
    }

    this->getControllable()->updateAck();
}

void UiLr2Controller::control()
{
    if (m_controlPointChanged) {
        this->getControllable()->set(VID_CONTROL_POINT_INDEX, m_controlPointIndex);
        this->getControllable()->set(VID_CONTROL_POINT_VALUE, m_controlPoints[m_controlPointIndex].values);
        this->getControllable()->control(CMD_CONTROL_POINT_SET);

        m_controlPointChanged = false;
    }

    if (m_knotChanged) {
        this->getControllable()->set(VID_KNOT_INDEX, m_knotIndex);
        this->getControllable()->set(VID_KNOT_VALUE, m_knots[m_knotIndex]);
        this->getControllable()->control(CMD_KNOT_SET);

        m_knotChanged = false;
    }

    if (m_degreeChanged) {
        this->getControllable()->set(VID_DEGREE_VALUE, m_degreeValue);
        this->getControllable()->control(CMD_DEGREE_SET);

        m_degreeChanged = false;
    }

    if (m_renderStepChanged) {
        this->getControllable()->set(VID_RENDER_STEP, m_renderStep);
        this->getControllable()->control(CMD_STEP_SET);

        m_renderStepChanged = false;
    }

    if (m_renderColorChanged) {
        this->getControllable()->set(VID_RENDER_COLOR, m_renderColor);
        this->getControllable()->control(CMD_COLOR_SET);

        m_renderColorChanged = false;
    }

    if (m_showControlPointsChanged) {
        this->getControllable()->set(VID_CONTROL_POINTS_FLAG, m_showControlPoints);
        this->getControllable()->control(CMD_SHOW_CONTROL_POINTS_SWITCH);

        m_showControlPointsChanged = false;
    }

    if (m_showControlPolygonChanged) {
        this->getControllable()->set(VID_CONTROL_POLYGON_FLAG, m_showControlPolygon);
        this->getControllable()->control(CMD_SOW_CONTROL_POLYGON_SWITCH);
        
        m_showControlPolygonChanged = false;
    }

    if (m_buttonUniformStep) {
        this->getControllable()->set(VID_KNOT_STEP, m_knotStep);
        this->getControllable()->control(CMD_KNOTS_UNIFORM);

        m_buttonUniformStep = false;
    }

    if (m_buttonOpenUniformStep) {
        this->getControllable()->set(VID_KNOT_STEP, m_knotStep);
        this->getControllable()->control(CMD_KNOTS_OPENUNIFORM);

        m_buttonOpenUniformStep = false;
    }

    if (m_buttonLegendRemember) {
        this->getControllable()->control(CMD_REMEMBER_SPLINE);

        SplineLegendInfo info;
        info.color[0] = m_renderColor[0];
        info.color[1] = m_renderColor[1];
        info.color[2] = m_renderColor[2];
        info.knots = this->knotsToString();
        info.degree = m_degreeValue;
        m_legend.push_back(info);

        m_buttonLegendRemember = false;
    }

    if (m_buttonLegendClear) {
        this->getControllable()->control(CMD_CLEAR_SPLINES);

        m_legend.clear();

        m_buttonLegendClear = false;
    }
}

void UiLr2Controller::renderUi()
{
    // UiSceneController2D::renderUi();
    ImGui::Begin("Spline Control");
    
    ImGui::SeparatorText("Degree");
    m_degreeChanged = ImGui::SliderInt("##", &m_degreeValue, 2, m_degreeMax);

    ImGui::SeparatorText("Control Points");
    for (int i = 0; i < m_controlPoints.size(); i++) {
        char buf[32];
        sprintf(buf, "B%d", i);

        if (!m_controlPointChanged) {
            m_controlPointIndex = i;
        }

        m_controlPointChanged |= ImGui::SliderFloat2(buf, m_controlPoints[i].values, -100.0, 100.0);
    }

    ImGui::SeparatorText("Knots");

    ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.3f);
    m_buttonUniformStep = ImGui::Button("Uniform");
    ImGui::SameLine();
    m_buttonOpenUniformStep = ImGui::Button("Open Uniform");
    ImGui::SameLine();
    ImGui::InputFloat("Step##Knots", &m_knotStep, 0.1);
    if (m_knotStep < 0) {
        m_knotStep = 0;
    }
    ImGui::PopItemWidth();

    ImGui::Spacing();
    ImGui::Spacing();
    
    float min, max;
    for (int i = 0; i < m_knots.size(); i++) {
        char buf[32];
        sprintf(buf, "x%d", i);

        if (!m_knotChanged) {
            m_knotIndex = i;
        }

        // Determine min for current knot        
        if (i == 0) {
            min = 0;
        } else {
            min = m_knots[i - 1];
        }

        // Determine max for current knot        
        if (i + 1 == m_knots.size()) {
            max = 20;
        } else {
            max = m_knots[i + 1];
        }

        m_knotChanged |= ImGui::SliderFloat(buf, &m_knots[i], min, max);

        // Check for borders
        if (m_knots[i] < min) m_knots[i] = min;
        if (m_knots[i] > max) m_knots[i] = max;
    }

    ImGui::SeparatorText("Render");
    m_renderColorChanged = ImGui::ColorEdit3("Color", m_renderColor, ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);
    m_renderStepChanged = ImGui::SliderFloat("Step##Render", &m_renderStep, 0.001, 1.0, "%.3f", ImGuiSliderFlags_Logarithmic);
    m_showControlPointsChanged = ImGui::Checkbox("Show Control Points", &m_showControlPoints);
    m_showControlPolygonChanged = ImGui::Checkbox("Show Polygon", &m_showControlPolygon);

    ImGui::End();

    ImGui::Begin("Legend");

    ImGui::SeparatorText("Control##Legend");
    m_buttonLegendRemember = ImGui::Button("Remember##Legend");
    ImGui::SameLine();
    m_buttonLegendClear = ImGui::Button("Clear##Legend");
    ImGui::SeparatorText("List##Legend");

    for (auto info : m_legend) {
        ImGui::ColorEdit3("##", info.color, ImGuiColorEditFlags_NoPicker | ImGuiColorEditFlags_NoOptions | ImGuiColorEditFlags_NoInputs);
        
        ImGui::SameLine();

        char buf[32];
        sprintf(buf, "Degree = %d", info.degree);
        ImGui::Text(buf);

        ImGui::Text(info.knots.c_str());

        ImGui::Separator();
    }

    ImGui::End();
}

std::string UiLr2Controller::knotsToString()
{
    std::stringstream stream;
    stream.precision(3);

    stream << "[ ";
    for (float knot : m_knots) {
        stream << knot << "; ";
    }
    stream << "]";

    return stream.str();
}
