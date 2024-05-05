#ifndef UISCENECONTROLLER_H_
#define UISCENECONTROLLER_H_

#include "glfwimguimanager.h"
#include "interfaces/controllable.h"

class UiSceneController : public GlfwImguiManager {
public:
    UiSceneController(GLFWwindow *w = nullptr);
    virtual ~UiSceneController();

    void setAreaMargins(int marginLeft = 0, int marginTop = 0, int marginRight = 0, int marginBottom = 0);

    void attachControllable(Controllable *c);
    void manage() override;

protected:
    struct Area {
        int x;
        int y;
        int width;
        int height;
    };

    const Area &getArea() const;
    float getAspectRatio() const;
    void updateArea();

    virtual void onWindowResize(GLFWwindow *w, int width, int height) override;

    virtual void initFromControllable() = 0;
    virtual void updateFromControllable() = 0;
    virtual void control() = 0;

private:
    Controllable *m_controllable;

    Area m_area;

    int m_marginLeft;
    int m_marginTop;
    int m_marginRight;
    int m_marginBottom;

};


#endif // UISCENECONTROLLER_H_