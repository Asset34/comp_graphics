#ifndef GLFWIMGUICONTROLMANAGER_H_
#define GLFWIMGUICONTROLMANAGER_H_

#include "ui/glfwimguimanager.h"
#include "interfaces/cameracontroller.h"
#include "interfaces/controllable.h"

class GlfwImguiControlManager : public GlfwImguiManager {
public:
    GlfwImguiControlManager(GLFWwindow *w = nullptr);
    virtual ~GlfwImguiControlManager();

    void attachController(CameraController *c);
    void attachControllable(Controllable *c);

    CameraController *getCameraController() const;
    Controllable *getControllable() const;

protected:
    void onWindowResize(GLFWwindow *w, int width, int height) override;
    void onMouseMovement(GLFWwindow *w, double xpos, double ypos) override;
    void onMouseScroll(GLFWwindow *w, double xoffset, double yoffset) override;

private:
    bool m_mouseFirstClick;
    float m_mouseLastx, m_mouseLasty;
    float m_mouseSensitivity;

    CameraController *m_controller;
    Controllable *m_controllable;

};

#endif // GlfwImguiCONTROLManager_H_