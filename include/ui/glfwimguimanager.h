#ifndef GLFWIMGUIMANAGER_H_
#define GLFWIMGUIMANAGER_H_

#include "abstract/uimanager.h"
#include "glfw/glfw3.h"

class GlfwImguiManager : public UiManager {
public:
    GlfwImguiManager(GLFWwindow *w = nullptr);
    virtual ~GlfwImguiManager();

    virtual void manage() override;
    void init(GLFWwindow *w);

protected:
    virtual void render();
    
    void renderBegin();
    void renderEnd();

    virtual void onWindowResize(GLFWwindow *w, int width, int height) {};
    virtual void onMouseMovement(GLFWwindow *w, double xpos, double ypos) {};
    virtual void onMouseScroll(GLFWwindow *w, double xoffset, double yoffset) {};
    virtual void onKey(GLFWwindow *w, int key, int scancode, int action, int mods) {};

    GLFWwindow *getWindowPtr() const;

private:
    void init();
    void destroy();

    // Event handlers
    static void onWindowResizeEvent(GLFWwindow *w, int width, int height);
    static void onMouseMovementEvent(GLFWwindow *w, double xpos, double ypos);
    static void onMouseScrollEvent(GLFWwindow *w, double xoffset, double yoffset);
    static void onKeyEvent(GLFWwindow *w, int key, int scancode, int action, int mods);

    static GlfwImguiManager *retrieveThis(GLFWwindow *window);

    GLFWwindow *m_window;

    

};


#endif // GLFWIMGUIMANAGER_H_