#ifndef UILR3CONTROLLER_H_
#define UILR3CONTROLLER_H_

#include "uiscenecontroller3d.h"
#include <vector>

class UiLr3Controller : public UiSceneController3D {
public:
    UiLr3Controller(GLFWwindow *w = nullptr, bool manageContext = false);
    ~UiLr3Controller() {}

protected:
    void initFromControllable() override;
    void updateFromControllable() override;
    void control() override;

    void renderUi() override;

private:

    enum Commands {
        CMD_SET_SURFACE_HEIGHT,
        CMD_SET_SURFACE_WIDTH,
        CMD_SET_SURFACE_ROW_VALUE,
        CMD_SET_SURFACE_COLUMN_VALUE,
        CMD_SET_SURFACE_VALUE,
        CMD_HKNOT_SET,
        CMD_HKNOTS_UNIFORM,
        CMD_HKNOTS_OPENUNIFORM,
        CMD_WKNOT_SET,
        CMD_WKNOTS_UNIFORM,
        CMD_WKNOTS_OPENUNIFORM,
        CMD_HDEGREE_SET,
        CMD_WDEGREE_SET,
        CMD_HSTEP_SET,
        CMD_WSTEP_SET,
        CMD_SHOW_CONTROL_POINTS_SWITCH,
        CMD_SHOW_CONTROL_POLYGON_SWITCH
    };

    enum ValueIds {
        VID_SURFACE_HEIGHT,
        VID_SURFACE_WIDTH,
        VID_SURFACE_ROW,
        VID_SURFACE_COLUMN,
        VID_SURFACE_ROW_VALUE,
        VID_SURFACE_COLUMN_VALUE,
        VID_SURFACE_VALUE,
        VID_KNOT_INDEX,
        VID_KNOT_VALUE,
        VID_HKNOT_SIZE,
        VID_WKNOT_SIZE,
        VID_HKNOTS,
        VID_WKNOTS,
        VID_KNOT_STEP,
        VID_HDEGREE_VALUE,
        VID_HDEGREE_MAX,
        VID_WDEGREE_VALUE,
        VID_WDEGREE_MAX,
        VID_HSTEP,
        VID_WSTEP,
        VID_CONTROL_POINTS_FLAG,
        VID_CONTROL_POLYGON_FLAG
    };

    std::vector<float> m_surfaceColumnValues;
    std::vector<float> m_surfaceRowValues;
    std::vector<std::vector<float>> m_surfaceValues;
    std::vector<float> m_hknots;
    std::vector<float> m_wknots;

    int m_surfaceHeight;
    int m_surfaceWidth;
    int m_surfaceColumn;
    int m_surfaceRow;
    float m_controlPointValue;

    int m_hdegree, m_wdegree;
    int m_hdegreeMax, m_wdegreeMax;

    int m_hknotIndex, m_wknotIndex;
    float m_hknotStep, m_wknotStep;

    float m_hrenderStep, m_wrenderStep;

    bool m_buttonUniformHKnots;
    bool m_buttonOpenUniformHKnots;
    bool m_buttonUniformWKnots;
    bool m_buttonOpenUniformWKnots;

    bool m_surfaceHeightChanged;
    bool m_surfaceWidthChanged;
    bool m_surfaceColumnValueChanged;
    bool m_surfaceRowValueChanged;
    bool m_controlPointValueChanged;
    bool m_hknotChanged;
    bool m_wknotChanged;
    bool m_hdegreeChanged;
    bool m_wdegreeChanged;
    bool m_hrenderStepChanged;
    bool m_wrenderStepChanged;

    bool m_showControlPoints;
    bool m_showControlPointsChanged;

    bool m_showControlPolygon;
    bool m_showControlPolygonChanged;

};

#endif // UILR3CONTROLLER_H_