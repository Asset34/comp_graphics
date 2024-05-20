#ifndef UILR3CONTROLLER_H_
#define UILR3CONTROLLER_H_

#include "uiscenecontroller3d.h"

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
    };

    enum ValueIds {
    };


    int m_rowSize = 4;
    int m_columnSize = 4;
    int m_selectedRow = 1;
    int m_selectedColumn = 1;
    bool m_pointSelectedChanged = false;

    float m_point[3];
    bool m_pointChanged = false;


};

#endif // UILR3CONTROLLER_H_