#ifndef LR1UIMANAGER_H_
#define LR1UIMANAGER_H_

#include "interfaces/controllable.h"
#include "glfwimguicontrolmanager.h"

class LR1UiManager : public GlfwImguiControlManager {
public:
    LR1UiManager(GLFWwindow *w = nullptr);
    ~LR1UiManager();

    virtual void render() override;

private:
    float m_shapePos[3];
    float m_lineBegin[3];
    float m_lineEnd[3];
    float m_angle;

};

#endif // LR1UIMANAGER_H_