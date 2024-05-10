#ifndef UISCENECONTROLLER2D_H_
#define UISCENECONTROLLER2D_H_

#include "uiscenecontroller.h"
#include "interfaces/observationcontroller2d.h"

class UiSceneController2D : public UiSceneController {
public:
    UiSceneController2D(GLFWwindow *w = nullptr, bool manageContext = false);
    virtual ~UiSceneController2D();

    void attachObservationController(ObservationController2D *c);

protected:
    void onWindowResize(GLFWwindow *w, int width, int height) override;
    void onMouseMovement(GLFWwindow *w, double xpos, double ypos) override;
    void onMouseScroll(GLFWwindow *w, double xoffset, double yoffset) override;
    void onKey(GLFWwindow *w, int key, int scancode, int action, int mods) override;

private:
    ObservationController2D *m_observationController;
    
    bool m_mouseFirstClick;
    float m_mouseLastx, m_mouseLasty;
        
};

#endif // UISCENECONTROLLER2D_H_