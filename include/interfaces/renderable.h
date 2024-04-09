#ifndef RENDERABLE_H_
#define RENDERABLE_H_

#include "glm/glm.hpp"

struct RenderData {};

class Renderable {
public:
    virtual RenderData getRenderData() = 0;
    virtual glm::mat4 getTransformation() = 0;

    virtual ~Renderable() {};

};

#endif // RENDERABLE_H_