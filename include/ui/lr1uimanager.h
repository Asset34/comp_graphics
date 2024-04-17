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
    float m_posx, m_posy, m_posz;

    float m_anglex, m_angley, m_anglez;

    float m_lineBeginx, m_lineBeginy, m_lineBeginz;
    float m_lineEndx, m_lineEndy, m_lineEndz;

};

#endif // LR1UIMANAGER_H_