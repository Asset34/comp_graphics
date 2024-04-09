#ifndef RENDERER_H_
#define RENDERER_H_

#include "interfaces/renderprovider.h"

class Renderer {
public:
    Renderer();
    virtual ~Renderer() {};

    virtual void init() = 0;
    virtual void attach(RenderProvider *p);
    virtual void updateData() = 0;
    virtual void render() = 0;

protected:
    RenderProvider *m_provider;
    
};

#endif // RENDERER_H_