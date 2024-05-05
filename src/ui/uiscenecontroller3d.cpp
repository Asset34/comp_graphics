#include "glad/glad.h"
#include "ui/uiscenecontroller3d.h"

UiSceneController3D::UiSceneController3D(GLFWwindow * w)
    : UiSceneController(w),
      m_observationController(nullptr),
      m_mouseFirstClick(true),
      m_translationSensitivity(0.25),
      m_rotationSensitivity(0.5)
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

void UiSceneController3D::setTranslationSensitivity(float sensitivity)
{
    m_translationSensitivity = sensitivity;
}

void UiSceneController3D::setRotatonSensitivity(float sensitivity)
{
    m_rotationSensitivity = sensitivity;
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

    // Get buttons
    int mouseRightButton = glfwGetMouseButton(w, GLFW_MOUSE_BUTTON_RIGHT);
    int key = glfwGetKey(w, GLFW_KEY_LEFT_SHIFT);

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
        float offsetx = xpos - m_mouseLastx;
        float offsety = ypos - m_mouseLasty;
        
        // Remember last position
        m_mouseLastx = xpos;
        m_mouseLasty = ypos;

        if (key == GLFW_PRESS) {
            // Control camera translation
            m_observationController->translateSide(-offsetx * m_translationSensitivity);
            m_observationController->translateForward(offsety * m_translationSensitivity);
        } else {
            // Control camera rotation
            m_observationController->rotateHorizontal(-offsetx * m_rotationSensitivity);
            m_observationController->rotateVertical(-offsety * m_rotationSensitivity);
        }
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