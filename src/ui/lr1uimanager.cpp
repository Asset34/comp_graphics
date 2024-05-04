#include "ui/lr1uimanager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

LR1UiManager::LR1UiManager(GLFWwindow * w)
    : GlfwImguiControlManager(w)
{
    m_lineBegin[0] = 30;
    m_lineBegin[1] = -30;
    m_lineBegin[2] = 20;

    m_lineEnd[0] = 30;
    m_lineEnd[1] = 30;
    m_lineEnd[2] = -20;

    m_shapePos[0] = 0;
    m_shapePos[1] = 0;
    m_shapePos[2] = 0;

    m_angle = 0;
}

LR1UiManager::~LR1UiManager()
{
}

void LR1UiManager::render()
{
    Controllable *c = this->getControllable();

    // Get controllable state
    float shapePos[3];
    float lineBegin[3];
    float lineEnd[3];
    float angle;

    c->sendValue(0, shapePos[0]);
    c->sendValue(1, shapePos[1]);
    c->sendValue(2, shapePos[2]);
    c->sendValue(3, angle);

    // Update
    if (c->changed()) {
        m_shapePos[0] = shapePos[0];
        m_shapePos[1] = shapePos[1];
        m_shapePos[2] = shapePos[2];

        // std::cout << angle << std::endl;

        // m_angle = 0;
        m_angle = angle;
    }
    c->changeAck();

    // Render
    this->renderBegin();

    ImGui::Begin("Parameters");
    ImGui::SliderFloat3("Shape position", m_shapePos, -100.0f, 100.0f);
    ImGui::SliderFloat3("Line - begin", m_lineBegin, -100.0f, 100.0f);
    ImGui::SliderFloat3("Line - end", m_lineEnd, -100.0f, 100.0f);
    ImGui::SliderFloat("Angle", &m_angle, -360.0f, 360.0f, "%.0f deg");
    ImGui::End();

    // ImGui::ShowDemoWindow();
    this->renderEnd();

    //  Movement control
    float movex = m_shapePos[0] - shapePos[0];
    float movey = m_shapePos[1] - shapePos[1];
    float movez = m_shapePos[2] - shapePos[2];
    bool control = false;
    if (movex) {
        c->receiveValue(0, movex);
        control = true;
    }
    if (movey) {
        c->receiveValue(1, movey);
        control = true;
    }
    if (movez) {
        c->receiveValue(2, movez);
        control = true;
    }
    if (control) {
        c->control(0);
    }

    // Line control
    c->receiveValue(6,  m_lineBegin[0]);
    c->receiveValue(7,  m_lineBegin[1]);
    c->receiveValue(8,  m_lineBegin[2]);
    c->receiveValue(9,  m_lineEnd[0]);
    c->receiveValue(10, m_lineEnd[1]);
    c->receiveValue(11, m_lineEnd[2]);
    c->control(1);

    // Rotation control
    float rotate = m_angle - angle;
    if (rotate) {
        c->receiveValue(12, rotate);
        c->control(2);
    }
}
