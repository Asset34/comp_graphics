#include "ui/uicontroller.h"

UiController::UiController(GLFWwindow * w)
    : GlfwImguiManager(w),
      m_controllable(nullptr)
{
}

UiController::~UiController()
{
}

void UiController::attachControllable(Controllable *c)
{
    m_controllable = c;
    this->initFromControllable();
}

void UiController::manage()
{
    if (!m_controllable) {
        return;
    }

    if(m_controllable->updated()) {
        this->updateFromControllable();
        m_controllable->updateAck();
    }

    this->render();
    this->control();
}
