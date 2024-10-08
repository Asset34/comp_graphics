#ifndef UISCENECONTROLLER3D_H_
#define UISCENECONTROLLER3D_H_

#include "uiscenecontroller.h"
#include "interfaces/observationcontroller3d.h"

class UiSceneController3D : public UiSceneController {
public:
    UiSceneController3D(GLFWwindow *w = nullptr, bool manageContext = false);
    virtual ~UiSceneController3D();

    void attachObservationController(ObservationController3D *c);

    void setTranslationSensitivity(float sensitivity);
    void setRotatonSensitivity(float sensitivity);

protected:
    void onWindowResize(GLFWwindow *w, int width, int height) override;
    void onMouseMovement(GLFWwindow *w, double xpos, double ypos) override;
    void onMouseScroll(GLFWwindow *w, double xoffset, double yoffset) override;
    void onKey(GLFWwindow *w, int key, int scancode, int action, int mods) override;

private:
    ObservationController3D *m_observationController;
    
    bool m_mouseFirstClick;
    float m_mouseLastx, m_mouseLasty;

    float m_translationSensitivity;
    float m_rotationSensitivity;
        
};

#endif // UISCENECONTROLLER3D_H_