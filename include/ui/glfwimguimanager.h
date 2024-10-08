#ifndef GLFWIMGUIMANAGER_H_
#define GLFWIMGUIMANAGER_H_

#include "abstract/uimanager.h"
#include "glfw/glfw3.h"

class GlfwImguiManager : public UiManager {
public:
    GlfwImguiManager(GLFWwindow *w = nullptr, bool manageContext = false);
    virtual ~GlfwImguiManager();

    virtual void manage() override;
    virtual void update() override;

    void init(GLFWwindow *w, bool manageContext = false);

    void manageContext();
    void stopManagingContext();

    void handlePreRendering();
    void stopHandingPreRendering();

    void handlePostRendering();
    void stopHandingPostRendering();

protected:
    void render();
    virtual void renderUi();
    
    virtual void initLogic() {};

    virtual void onWindowResize(GLFWwindow *w, int width, int height) {};
    virtual void onMouseMovement(GLFWwindow *w, double xpos, double ypos) {};
    virtual void onMouseScroll(GLFWwindow *w, double xoffset, double yoffset) {};
    virtual void onKey(GLFWwindow *w, int key, int scancode, int action, int mods) {};

    GLFWwindow *getWindowPtr() const;

private:
    void initContext();
    void destroyContext();
    void preRendering();
    void postRendering();

    static bool m_contextManagerAssigned;
    static bool m_contextInitialized;
    static bool m_preRenderingHandled;
    static bool m_postRenderingHandled;
    static int m_preRenderingHandlers;
    static int m_postRenderingHandlers;

    // Event handlers
    static void onWindowResizeEvent(GLFWwindow *w, int width, int height);
    static void onMouseMovementEvent(GLFWwindow *w, double xpos, double ypos);
    static void onMouseScrollEvent(GLFWwindow *w, double xoffset, double yoffset);
    static void onKeyEvent(GLFWwindow *w, int key, int scancode, int action, int mods);

    static GlfwImguiManager *retrieveThis(GLFWwindow *window);

    bool m_manageContext;
    bool m_handlePreRendering;
    bool m_handlePostRendering;

    GLFWwindow *m_window;

};


#endif // GLFWIMGUIMANAGER_H_