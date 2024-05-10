#ifndef WINDOW_H_
#define WINDOW_H_

#include <string>
#include "glad/glad.h"
#include "glfw/glfw3.h"
#include "workspace.h"
#include "ui/uiwindowcontroller.h"
#include <vector>

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    UiManager *getCurrentUiManager() const;
    GLFWwindow* getGlfwWindow();

    void draw();
    bool shouldClose() const;
    int getCurrentWorkspaceIndex() const;
    std::vector<std::string> getWorkspacesNames() const;
    int getWorkspacesNumber() const;

    void setCurrentWorkspace(int index);

private:
    void initRenderer();
    void setupMainUiController();
    void setupWorkspaces();

    GLFWwindow* m_window;
    std::string m_title;
    int m_width, m_height;

    UiWindowController m_uiController;

    std::vector<Workspace> m_workspaces;
    int m_currentWorkspaceIndex;
    Workspace *m_currentWorkspace;

};

#endif // WINDOW_H_