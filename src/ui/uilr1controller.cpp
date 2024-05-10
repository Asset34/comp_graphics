#include "ui/uilr1controller.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

UiLr1Controller::UiLr1Controller(GLFWwindow * w, bool manageContext)
    : UiSceneController3D(w, manageContext),
      m_shapeChanged(false),
      m_lineBeginChanged(false),
      m_lineEndChanged(false),
      m_rotationAngleChanged(false)
{
}

UiLr1Controller::~UiLr1Controller()
{
}

void UiLr1Controller::initFromControllable()
{
    // Init Shape
    this->getControllable()->get(VID_SHAPE_POS, m_shapePos);

    // Init Line
    this->getControllable()->get(VID_LINE_BEGIN_POS, m_lineBegin);
    this->getControllable()->get(VID_LINE_END_POS, m_lineEnd);

    // Init angle
    this->getControllable()->get(VID_ROTATION_ANGLE, m_rotationAngle);
}

void UiLr1Controller::updateFromControllable()
{
    if (!this->getControllable()->updated()) return;

    for (auto i : this->getControllable()->getUpdateList()) {
        switch (i)
        {
        case VID_SHAPE_POS:
            this->getControllable()->get(VID_SHAPE_POS, m_shapePos);
        break;
        case VID_LINE_BEGIN_POS:
            this->getControllable()->get(VID_LINE_BEGIN_POS, m_lineBegin);
        break;
        case VID_LINE_END_POS:
            this->getControllable()->get(VID_LINE_END_POS, m_lineEnd);
        break;
        case VID_ROTATION_ANGLE:
            this->getControllable()->get(VID_ROTATION_ANGLE, m_rotationAngle);
        break;
        }
    }

    this->getControllable()->updateAck();
}

void UiLr1Controller::control()
{
    if (m_shapeChanged) {
        this->getControllable()->set(VID_SHAPE_POS, m_shapePos);
        this->getControllable()->control(CMD_SHAPE_SET);

        m_shapeChanged = false;
    }
    if (m_lineBeginChanged) {
        this->getControllable()->set(VID_LINE_BEGIN_POS, m_lineBegin);
        this->getControllable()->control(CMD_LINE_BEGIN_SET);

        m_lineBeginChanged = false;
    }
    if (m_lineEndChanged) {
        this->getControllable()->set(VID_LINE_END_POS, m_lineEnd);
        this->getControllable()->control(CMD_LINE_END_SET);

        m_lineEndChanged = false;
    }
    if (m_rotationAngleChanged) {
        this->getControllable()->set(VID_ROTATION_ANGLE, m_rotationAngle);
        this->getControllable()->control(CMD_ROTATE);

        m_rotationAngleChanged = false;
    }
}

void UiLr1Controller::renderUi()
{
    ImGui::Begin("Shape");
    m_shapeChanged |= ImGui::SliderFloat3("Position", m_shapePos, -200, 200);
    m_lineBeginChanged |= ImGui::SliderFloat3("Line (x1)", m_lineBegin, -200, 200);
    m_lineEndChanged |= ImGui::SliderFloat3("Line (x2)", m_lineEnd, -200, 200);
    m_rotationAngleChanged |= ImGui::SliderFloat("Rotation Angle", &m_rotationAngle, -360.0, 360.0, "%.0f deg");
    ImGui::End();
}
