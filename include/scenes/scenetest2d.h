#ifndef SCENETEST2D_H_
#define SCENETEST2D_H_

#include "interfaces/controllable.h"
#include "scenes/scene2d.h"

class SceneTest2D : public Scene2D, public Controllable {
public:
    SceneTest2D();
    ~SceneTest2D();

    void update() override {};

    void control(int cmd) override {};
    bool updated() override {return false;};
    void updateAck() override {};
    std::list<int> getUpdateList() override {return {};};

private:


};

#endif // SCENETEST2D_H_