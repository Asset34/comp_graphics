#include "glad/glad.h"
#include "ui/glfwimguicontrolmanager.h"

GlfwImguiControlManager::GlfwImguiControlManager(GLFWwindow *w)
    :GlfwImguiManager(w),
     m_mouseFirstClick(true),
     m_mouseSensitivity(1.0),
     m_controller(nullptr)
{
}

GlfwImguiControlManager::~GlfwImguiControlManager()
{
}

void GlfwImguiControlManager::attachController(CameraController *c)
{
    m_controller = c;
}

void GlfwImguiControlManager::attachControllable(Controllable *c)
{
    m_controllable = c;
}

CameraController *GlfwImguiControlManager::getCameraController() const
{
    return m_controller;
}

Controllable *GlfwImguiControlManager::getControllable() const
{
    return m_controllable;
}

void GlfwImguiControlManager::onWindowResize(GLFWwindow *w, int width, int height)
{
    // Check
    if (!m_controller) return;
    
    m_controller->setAspectRatio((float) width / height);
    glViewport(0, 0, width, height);
}

void GlfwImguiControlManager::onMouseMovement(GLFWwindow *w, double xpos, double ypos)
{
    // Check
    if (!m_controller) return;

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
        m_controller->rotateYaw(-offsetx);
        m_controller->rotatePitch(-offsety);
        
    } else {
        m_mouseFirstClick = true;
    }
}

void GlfwImguiControlManager::onMouseScroll(GLFWwindow *w, double xoffset, double yoffset)
{
    // Check
    if (!m_controller) return;

    // Process event
    if (yoffset > 0) m_controller->ZoomIn();
    else m_controller->ZoomOut();
}
