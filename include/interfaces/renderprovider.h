#ifndef RENDERPROVIDER_H_
#define RENDERPROVIDER_H_

#include <vector>
#include "renderable.h"

struct RenderProviderData {};

class RenderProvider {
public:
    virtual RenderProviderData getRenderProviderData() = 0;
    virtual const std::vector<Renderable*> &getRenderables() = 0;
    virtual const std::vector<int> &getRenderableUpdateVector() = 0;

    virtual ~RenderProvider() {};

};

#endif// RENDERPROVIDER_H_