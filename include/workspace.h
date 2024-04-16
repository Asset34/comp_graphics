#include <string>
#include "abstract/scene.h"
#include "abstract/renderer.h"
#include "abstract/uimanager.h"

class Workspace {
public:
    Workspace();
    ~Workspace();

    void attach(Scene *scene, Renderer *renderer, UiManager *manager);
    UiManager *getUiManager() const;
    void run();

private:
    std::string title;

    Scene *m_scene;
    Renderer *m_renderer;
    UiManager *m_uiManager;

};