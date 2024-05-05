#ifndef SCENELR1_H_
#define SCENELR1_H_

#include "interfaces/controllable.h"
#include "scenes/scene3d.h"
#include "objects/shape.h"
#include "objects/line.h"

class SceneLR1 : public Scene3D, public Controllable {
public:
    SceneLR1();
    ~SceneLR1();

    void update() override;
    std::vector<int> getRenderableUpdateVector() override;

    void control(int cmd) override;
    bool updated() override;
    void updateAck() override;
    std::list<int> getUpdateList() override;

private:
    Shape m_shape;
    Line m_line;

    bool m_changed;

    vec3 m_shapeMove;
    vec3 m_lineBegin;
    vec3 m_lineEnd;
    float m_rotationAngle;
    float m_angle;

    bool m_lineFlag;

};

#endif // SCENELR1_H_