#include <string>
#include "abstract/scene.h"
#include "abstract/renderer.h"
#include "abstract/uimanager.h"

class Workspace {
public:
    Workspace(const std::string name = "Unnamed");
    ~Workspace();

    void attach(Scene *scene, Renderer *renderer, UiManager *manager);
    void run();
    void update();

    void setName(const std::string &name);
    const std::string getName() const;

    UiManager *getUiManager() const;

private:
    std::string m_name;

    Scene *m_scene;
    Renderer *m_renderer;
    UiManager *m_uiManager;

};