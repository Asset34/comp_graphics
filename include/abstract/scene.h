#ifndef SCENE_H_
#define SCENE_H_

#include "geometry.h"

class Scene {
public:
    virtual ~Scene() {};

    virtual void update() = 0;

    void setBackgroundColor(const Color &color);
    const Color &getBackgroundColor() const;

private:
    static const Color BACKGROUND_COLOR;

    Color m_backgroundColor = BACKGROUND_COLOR;

};

#endif // SCENE_H_