#ifndef SCENE_H_
#define SCENE_H_

#include "interfaces/renderprovider.h"

class Scene : public RenderProvider {
public:
    virtual ~Scene() {};
    virtual void update() = 0;

};

#endif // SCENE_H_