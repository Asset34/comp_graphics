#ifndef UILR1CONTROLLER_H_
#define UILR1CONTROLLER_H_

#include "uiscenecontroller3d.h"

class UiLr1Controller : public UiSceneController3D {
public:
    UiLr1Controller(GLFWwindow *w = nullptr);
    ~UiLr1Controller();

protected:
    void initFromControllable() override;
    void updateFromControllable() override;
    void control() override;

    void render() override;

private:
    enum Commands {
        CMD_SHAPE_SET = 0,
        CMD_LINE_BEGIN_SET = 1,
        CMD_LINE_END_SET = 2,
        CMD_ROTATE = 3
    };

    enum ValueIds {
        VID_SHAPE_POS = 0,
        VID_LINE_BEGIN_POS = 1,
        VID_LINE_END_POS = 2,
        VID_ROTATION_ANGLE = 3
    };

    float m_shapePos[3];
    bool m_shapeChanged;

    float m_lineBegin[3], m_lineEnd[3];
    bool m_lineBeginChanged, m_lineEndChanged;

    float m_rotationAngle;
    bool m_rotationAngleChanged;

};

#endif // UILR1CONTROLLER_H_