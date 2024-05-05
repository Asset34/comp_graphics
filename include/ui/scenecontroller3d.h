#ifndef SCENECONTROLLER_H_
#define SCENECONTROLLER_H_

#include "uicontroller.h"
#include "interfaces/observationcontroller3d.h"

class SceneController3D : public UiController {
public:
    SceneController3D(GLFWwindow *w = nullptr);
    virtual ~SceneController3D();

    void attachObservationController(ObservationController3D *c);
    void setMouseSensitivity(float sensitivity);

protected:
    void onWindowResize(GLFWwindow *w, int width, int height) override;
    void onMouseMovement(GLFWwindow *w, double xpos, double ypos) override;
    void onMouseScroll(GLFWwindow *w, double xoffset, double yoffset) override;

private:
    static const float DEFAULT_SENSITIVITY; // 1.0

    void initObservationObj();

    ObservationController3D *m_observationController;
    
    bool m_mouseFirstClick;
    float m_mouseLastx, m_mouseLasty;
    float m_mouseSensitivity;
    
};

#endif // SCENECONTROLLER_H_