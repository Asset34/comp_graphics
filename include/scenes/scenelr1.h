#ifndef SCENELR1_H_
#define SCENELR1_H_

#include "interfaces/controllable.h"
#include "scenes/basicscene.h"
#include "objects/shape.h"
#include "objects/line.h"

class SceneLR1 : public BasicScene, public Controllable {
public:
    SceneLR1();
    ~SceneLR1();

    void update() override;

    void control(int controlId) override;
    void receiveValue(int valueId, float sendValue) override;
    void sendValue(int valueId, float &receiver) override;
    bool changed() override;
    void changeAck() override;

    std::vector<int> getRenderableUpdateVector() override;

private:
    Shape m_shape;
    Line m_line;

    bool m_changed;

    vec3 m_shapeMove;
    vec3 m_lineBegin;
    vec3 m_lineEnd;
    float m_rotationAngle;
    float m_angle;

};

#endif // SCENELR1_H_