#ifndef WINDOW_H_H
#define WINDOW_H_H

#include <string>
#include "glad/glad.h"
#include "glfw/glfw3.h"
// #include "abstract/scene.h"
// #include "abstract/renderer.h"
// #include "abstract/uimanager.h"
#include "workspace.h"

class Window {
public:
    Window(const std::string &title, int width, int height);
    ~Window();

    UiManager *getCurrentUiManager() const;

    void draw();
    bool shouldClose() const;

private:
    GLFWwindow* m_window;
    std::string m_title;
    int m_width, m_height;

    Workspace m_workspace;

};

#endif // WINDOW_H_H