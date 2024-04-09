#ifndef RENDERPROVIDER_H_
#define RENDERPROVIDER_H_

#include <vector>
#include "glm/glm.hpp"
#include "renderable.h"

struct RenderProviderData {
    // Types
    typedef glm::vec3 Color;

    // Data
    std::vector<Renderable> Renderables;

    // Matrices
    glm::mat4 ViewMatrix = glm::mat4(1); // Default: Identity Matrix
    glm::mat4 ProjMatrix = glm::mat4(1); // Default: Identity Matrix

    // Visual
    Color BackgroundColor;

};

class RenderProvider {
public:
    virtual RenderProviderData getRenderProviderData() = 0;
    virtual const std::vector<Renderable*> &getRenderables() = 0;
    virtual const std::vector<int> &getRenderableUpdateVector() = 0;

    virtual ~RenderProvider() {};

};

#endif// RENDERPROVIDER_H_