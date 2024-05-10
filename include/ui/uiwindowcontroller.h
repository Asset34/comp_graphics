#ifndef UIWINDOWCONTROLLER_H_
#define UIWINDOWCONTROLLER_H_

#include "glfwimguimanager.h"
#include <vector>
#include <string>

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
    std::vector<std::string> m_workspacesNames;

    bool m_changed;

    Window *m_window;

};

#endif // UIWINDOWCONTROLLER_H_