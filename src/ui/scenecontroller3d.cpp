#include "glad/glad.h"
#include "ui/scenecontroller3d.h"

const float SceneController3D::DEFAULT_SENSITIVITY = 1.0;

SceneController3D::SceneController3D(GLFWwindow * w)
    : UiController(w),
      m_observationController(nullptr),
      m_mouseFirstClick(true),
      m_mouseSensitivity(DEFAULT_SENSITIVITY)
{
}

SceneController3D::~SceneController3D()
{
}

void SceneController3D::attachObservationController(ObservationController3D *c)
{
    m_observationController = c;
    this->initObservationObj();
}

void SceneController3D::setMouseSensitivity(float sensitivity)
{
    m_mouseSensitivity = sensitivity;
}

void SceneController3D::onWindowResize(GLFWwindow *w, int width, int height)
{
    // Check
    if (!m_observationController) return;
    
    m_observationController->setAspectRatio((float) width / height);
    glViewport(0, 0, width, height);
}

void SceneController3D::onMouseMovement(GLFWwindow *w, double xpos, double ypos)
{
    // Check
    if (!m_observationController) return;

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

void SceneController3D::onMouseScroll(GLFWwindow *w, double xoffset, double yoffset)
{
    // Check
    if (!m_observationController) return;

    // Process event
    if (yoffset > 0) m_observationController->zoomIn();
    else m_observationController->zoomOut();
}

void SceneController3D::initObservationObj()
{
    // Init aspect ration
    int width, height;
    glfwGetWindowSize(this->getWindowPtr(), &width, &height);
    m_observationController->setAspectRatio((float) width / height);
}
