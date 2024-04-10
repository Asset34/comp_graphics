#ifndef GLFWIMGUIMANAGER_H_
#define GLFWIMGUIMANAGER_H_

#include "abstract/uimanager.h"
#include "scenes/basicscene.h"
#include "glfw/glfw3.h"

class GlfwImguiManager : public UiManager {
public:
    GlfwImguiManager(GLFWwindow *w = nullptr);
    virtual ~GlfwImguiManager();

    virtual void init(GLFWwindow *w);

protected:
    void renderBegin();
    void renderEnd();

private:
    void init();
    void destroy();

    GLFWwindow *m_window;

};


#endif // GLFWIMGUIMANAGER_H_