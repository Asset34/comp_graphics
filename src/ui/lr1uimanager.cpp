#include "ui/lr1uimanager.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

LR1UiManager::LR1UiManager(GLFWwindow * w)
    : GlfwImguiControlManager(w)
{
}

LR1UiManager::~LR1UiManager()
{
}

void LR1UiManager::render()
{
    Controllable *c = this->getControllable();

    // Get controllable state
    float posx, posy, posz;
    float anglex, angley, anglez;
    c->sendValue(0, posx);
    c->sendValue(1, posy);
    c->sendValue(2, posz);
    c->sendValue(3, anglex);
    c->sendValue(4, angley);
    c->sendValue(5, anglez);

    // Update
    if (c->changed()) {
        m_posx = posx;
        m_posy = posy;
        m_posz = posz;
        m_anglex = anglex;
        m_angley = angley;
        m_anglez = anglez;
    }
    c->changeAck();

    // Render
    this->renderBegin();
    ImGui::SliderFloat("Pos_x", &m_posx, -50.0f, 50.0f);
    ImGui::SliderFloat("Pos_y", &m_posy, -50.0f, 50.0f);
    ImGui::SliderFloat("Pos_z", &m_posz, -50.0f, 50.0f);
    // ImGui::SliderFloat("Angle_x", c->controlFloat(3), -1.0f, 1.0f);
    ImGui::SliderFloat("Angle_x", &m_anglex, -360.0f, 360.0f);
    ImGui::SliderFloat("Angle_y", &m_angley, -360.0f, 360.0f);
    ImGui::SliderFloat("Angle_z", &m_anglez, -360.0f, 360.0f);
    this->renderEnd();

    //  Movement control
    float movex = m_posx - posx;
    float movey = m_posy - posy;
    float movez = m_posz - posz;
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

    // Rotation control
    float rotatex = m_anglex - anglex;
    float rotatey = m_angley - angley;
    float rotatez = m_anglez - anglez;
    control = false;
    if (rotatex) {
        c->receiveValue(3, rotatex);
        control = true;
    }
    if (rotatey) {
        c->receiveValue(4, rotatey);
        control = true;
    }
    if (rotatez) {
        c->receiveValue(5, rotatez);
        control = true;
    }
    if (control) {
        c->control(1);
    }
}
