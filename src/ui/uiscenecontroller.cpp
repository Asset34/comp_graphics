#include "glad/glad.h"
#include "ui/uiscenecontroller.h"

#include <iostream>

UiSceneController::UiSceneController(GLFWwindow * w)
    : GlfwImguiManager(w),
      m_marginLeft(0),
      m_marginTop(0),
      m_marginRight(0),
      m_marginBottom(0)
{
    this->updateArea();
}

UiSceneController::~UiSceneController()
{
}

void UiSceneController::setAreaMargins(int marginLeft, int marginTop, int marginRight, int marginBottom)
{
    m_marginLeft = marginLeft;
    m_marginTop = marginTop;
    m_marginRight = marginRight;
    m_marginBottom = marginBottom;

    this->updateArea();
}

void UiSceneController::attachControllable(Controllable *c)
{
    m_controllable = c;
    this->initFromControllable();
}

void UiSceneController::manage()
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

const UiSceneController::Area &UiSceneController::getArea() const
{
    return m_area;
}

float UiSceneController::getAspectRatio() const
{
    return (float) m_area.width / m_area.height;
}

void UiSceneController::updateArea()
{
    // Get window sizes
    int windowWidth, windowHeight;
    glfwGetWindowSize(this->getWindowPtr(), &windowWidth, &windowHeight);
    
    m_area.x = m_marginLeft;
    m_area.y = m_marginBottom;
    m_area.width = windowWidth - m_marginLeft - m_marginRight;
    m_area.height = windowHeight - m_marginTop - m_marginBottom;

    glViewport(m_area.x, m_area.y, m_area.width, m_area.height);
}

void UiSceneController::onWindowResize(GLFWwindow *w, int width, int height)
{
    this->updateArea();
}