#ifndef GLFWIMGUICAMERAMANAGER_H_
#define GLFWIMGUICAMERAMANAGER_H_

#include "ui/glfwimguimanager.h"
#include "interfaces/cameracontroller.h"

class GlfwImguiCameraManager : public GlfwImguiManager {
public:
    GlfwImguiCameraManager(GLFWwindow *w = nullptr);
    virtual ~GlfwImguiCameraManager();

    void attachController(CameraController *c);

protected:
    void onWindowResize(GLFWwindow *w, int width, int height) override;
    void onMouseMovement(GLFWwindow *w, double xpos, double ypos) override;
    void onMouseScroll(GLFWwindow *w, double xoffset, double yoffset) override;

private:
    bool m_mouseFirstClick;
    float m_mouseLastx, m_mouseLasty;
    float m_mouseSensitivity;

    CameraController *m_controller;

};

#endif // GlfwImguiCameraManager_H_