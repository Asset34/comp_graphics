#ifndef UIMANAGER_H_
#define UIMANAGER_H_

#include "glfw/glfw3.h"

#include "scene.h"

class UiManager {
public:
    UiManager();
    ~UiManager();

    void attachScene(Scene &scene);
    void attachWindow(GLFWwindow *w);

    void init();
    void newFrame();
    void render();

private:
    Scene *m_scene;
    GLFWwindow *m_window;

};

#endif // UIMANAGER_H_