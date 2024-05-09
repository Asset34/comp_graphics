#include "ui/uiscenecontroller2d.h"

#include <iostream>

UiSceneController2D::UiSceneController2D(GLFWwindow * w)
    : UiSceneController(w),
      m_observationController(nullptr),
      m_mouseFirstClick(true)
{
}

UiSceneController2D::~UiSceneController2D()
{
}

void UiSceneController2D::attachObservationController(ObservationController2D *c)
{
    m_observationController = c;
    m_observationController->setAspectRatio(this->getAspectRatio());
}

void UiSceneController2D::onWindowResize(GLFWwindow *w, int width, int height)
{
    // Check
    if (!m_observationController) return;

    UiSceneController::onWindowResize(w, width, height);

    m_observationController->setAspectRatio(this->getAspectRatio());
}

void UiSceneController2D::onMouseMovement(GLFWwindow *w, double xpos, double ypos)
{
    // Check
    if (!m_observationController) return;

    // Area check
    Area area = this->getArea();
    int windowWidth, windowHeight;
    glfwGetWindowSize(this->getWindowPtr(), &windowWidth, &windowHeight);
    if (xpos < area.x || xpos > (area.x + area.width)) return;
    if (ypos < (windowHeight - area.y - area.height) ||
        ypos > (windowHeight - area.y)) return;

    // Get buttons
    int mouseRightButton = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT);

    // Process first click
    if (mouseRightButton == GLFW_PRESS) {
        if (m_mouseFirstClick) {
            m_mouseLastx = xpos;
            m_mouseLasty = ypos;

            m_mouseFirstClick = false;
        }
    } else {
        m_mouseFirstClick = true;
    }

    // Perform actions
    if (mouseRightButton == GLFW_PRESS) {
        // Adjust offsets
        float relativeOffsetx = (xpos - m_mouseLastx) / windowWidth;
        float relativeOffsety = (ypos - m_mouseLasty) / windowHeight;

        // Remember last position
        m_mouseLastx = xpos;
        m_mouseLasty = ypos;

        // Control camera translation
        m_observationController->movex(-relativeOffsetx);
        m_observationController->movey(relativeOffsety);
    }
}

void UiSceneController2D::onMouseScroll(GLFWwindow *w, double xoffset, double yoffset)
{
    // Check
    if (!m_observationController) return;

    // Process event
    if (yoffset > 0) m_observationController->zoomIn();
    else m_observationController->zoomOut();
}

void UiSceneController2D::onKey(GLFWwindow *w, int key, int scancode, int action, int mods)
{
    // Check
    if (!m_observationController) return;

    // Process event
    if (key == GLFW_KEY_HOME && action == GLFW_PRESS) {
        m_observationController->home();
    }
}
