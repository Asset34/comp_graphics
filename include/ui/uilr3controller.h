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
        CMD_SET_SURFACE_VALUE
    };

    enum ValueIds {
        VID_SURFACE_HEIGHT,
        VID_SURFACE_WIDTH,
        VID_SURFACE_ROW,
        VID_SURFACE_COLUMN,
        VID_SURFACE_ROW_VALUE,
        VID_SURFACE_COLUMN_VALUE,
        VID_SURFACE_VALUE
    };

    std::vector<float> m_surfaceColumnValues;
    std::vector<float> m_surfaceRowValues;
    std::vector<std::vector<float>> m_surfaceValues;

    int m_surfaceHeight;
    int m_surfaceWidth;
    int m_surfaceColumn;
    int m_surfaceRow;
    float m_controlPointValue;

    bool m_surfaceHeightChanged;
    bool m_surfaceWidthChanged;
    bool m_surfaceColumnValueChanged;
    bool m_surfaceRowValueChanged;
    bool m_controlPointValueChanged;

};

#endif // UILR3CONTROLLER_H_