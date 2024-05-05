#ifndef UICONTROLLER_H_
#define UICONTROLLER_H_

#include "glfwimguimanager.h"
#include "interfaces/controllable.h"

class UiController : public GlfwImguiManager {
public:
    UiController(GLFWwindow *w = nullptr);
    virtual ~UiController();

    void attachControllable(Controllable *c);
    void manage() override;

protected:
    virtual void initFromControllable() = 0;
    virtual void updateFromControllable() = 0;
    virtual void control() = 0;

private:
    Controllable *m_controllable;

};

#endif // UICONTROLLER_H_