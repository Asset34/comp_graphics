#ifndef LR1CONTROLLER_H_
#define LR1CONTROLLER_H_

#include "scenecontroller3d.h"

class Lr1Controller : public SceneController3D {
public:
    Lr1Controller(GLFWwindow *w = nullptr);
    ~Lr1Controller();

protected:
    void initFromControllable() override;
    void updateFromControllable() override;
    void control() override;

// private:

};

#endif // LR1CONTROLLER_H_