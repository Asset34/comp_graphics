#ifndef SCENELR1_H_
#define SCENELR1_H_

#include <vector>
#include "shape.h"
#include "scenes/basicscene.h"

class SceneLR1 : public BasicScene {
public:
    SceneLR1();
    ~SceneLR1();

    void update() override;

private:
    Shape m_shape;

};

#endif // SCENELR1_H_