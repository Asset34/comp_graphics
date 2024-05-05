#include "glad/glad.h"
#include "ui/uiscenecontroller3d.h"

const float UiSceneController3D::DEFAULT_SENSITIVITY = 1.0;

UiSceneController3D::UiSceneController3D(GLFWwindow * w)
    : UiSceneController(w),
      m_observationController(nullptr),
      m_mouseFirstClick(true),
      m_mouseSensitivity(DEFAULT_SENSITIVITY)
{
}

UiSceneController3D::~UiSceneController3D()
{
}

void UiSceneController3D::attachObservationController(ObservationController3D *c)
{
    m_observationController = c;
    m_observationController->setAspectRatio(this->getAspectRatio());
}

void UiSceneController3D::setMouseSensitivity(float sensitivity)
{
    m_mouseSensitivity = sensitivity;
}

void UiSceneController3D::onWindowResize(GLFWwindow *w, int width, int height)
{
    // Check
    if (!m_observationController) return;

    this->updateArea();
    m_observationController->setAspectRatio(this->getAspectRatio());
}

void UiSceneController3D::onMouseMovement(GLFWwindow *w, double xpos, double ypos)
{
    // Check
    if (!m_observationController) return;

    // Area check
    Area area = this->getArea();
    if (xpos < area.x || xpos > (area.x + area.width)) return;
    if (ypos < area.y || ypos > (area.y + area.height)) return;

    // Process event
    int state = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT);
    if (state == GLFW_PRESS)
    {
        // Detect first click
        if (m_mouseFirstClick) {
            m_mouseLastx = xpos;
            m_mouseLasty = ypos;

            m_mouseFirstClick = false;
        }

        // Adjust offsets
        float offsetx = (xpos - m_mouseLastx) * m_mouseSensitivity;
        float offsety = (ypos - m_mouseLasty) * m_mouseSensitivity;
        
        // Remember last position
        m_mouseLastx = xpos;
        m_mouseLasty = ypos;

        // Control camera rotation
        m_observationController->rotateHorizontal(-offsetx);
        m_observationController->rotateVertical(-offsety);
        
    } else {
        m_mouseFirstClick = true;
    }
}

void UiSceneController3D::onMouseScroll(GLFWwindow *w, double xoffset, double yoffset)
{
    // Check
    if (!m_observationController) return;

    // Process event
    if (yoffset > 0) m_observationController->zoomIn();
    else m_observationController->zoomOut();
}