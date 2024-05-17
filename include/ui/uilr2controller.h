#ifndef UILR2CONTROLLER_H_
#define UILR2CONTROLLER_H_

#include "uiscenecontroller2d.h"

#include <vector>

class UiLr2Controller : public UiSceneController2D {
public:
    UiLr2Controller(GLFWwindow *w = nullptr, bool manageContext = false);
    ~UiLr2Controller();

protected:
    void initFromControllable() override;
    void updateFromControllable() override;
    void control() override;

    void renderUi() override;

private:
    enum Commands {
        CMD_CONTROL_POINT_SET,
        CMD_KNOT_SET,
        CMD_ORDER_SET,
        CMD_STEP_SET,
        CMD_SHOW_CONTROL_POINTS_SWITCH,
        CMD_SOW_CONTROL_POLYGON_SWITCH,
        CMD_KNOTS_UNIFORM,
        CMD_KNOTS_OPENUNIFORM
    };

    enum ValueIds {
        VID_CONTROL_POINT_SIZE,
        VID_CONTROL_POINT_INDEX,
        VID_CONTROL_POINT_VALUE,
        VID_KNOT_SIZE,
        VID_KNOT_INDEX,
        VID_KNOT_VALUE,
        VID_KNOTS,
        VID_ORDER_MAX,
        VID_ORDER_VALUE,
        VID_RENDER_STEP,
        VID_CONTROL_POINTS_FLAG,
        VID_CONTROL_POLYGON_FLAG,
        VID_KNOT_STEP
    };

    struct ControlPoint {
        float values[2];
    };

    std::vector<ControlPoint> m_controlPoints;
    int m_controlPointIndex;
    bool m_controlPointChanged;

    std::vector<float> m_knots;
    int m_knotIndex;
    bool m_knotChanged;

    int m_orderMax;
    int m_orderValue;
    bool m_orderChanged;

    float m_renderStep;
    bool m_renderStepChanged;

    float m_knotStep;
    
    bool m_buttonUniformStep;
    bool m_buttonOpenUniformStep;

    bool m_showControlPoints;
    bool m_showControlPointsChanged;

    bool m_showControlPolygon;
    bool m_showControlPolygonChanged;
};

#endif // UILR2CONTROLLER_H_