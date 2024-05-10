#ifndef UIWINDOWCONTROLLER_H_
#define UIWINDOWCONTROLLER_H_

// #include "window.h"
#include "glfwimguimanager.h"

class Window;

class UiWindowController : public GlfwImguiManager {
public: 
    UiWindowController(GLFWwindow *w = nullptr, bool manageContext = false);
    ~UiWindowController();

    void attach(Window *w);
    void manage() override;

protected:
    void renderUi() override;

private:
    void initFrom();
    void updateFrom();
    void control();

    int m_workspaceSelected;
    int m_workspacesNumber;
    bool m_changed;

    Window *m_window;

};

#endif // UIWINDOWCONTROLLER_H_