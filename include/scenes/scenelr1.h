#ifndef SCENELR1_H_
#define SCENELR1_H_

#include <vector>
#include "shape.h"
#include "interfaces/controllable.h"
#include "scenes/basicscene.h"

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

private:

    Shape m_shape;

    float m_shapeX, m_shapeY, m_shapeZ;
    float m_angleX;

    bool m_changed;

    float m_shapeMovex, m_shapeMovey, m_shapeMovez;
    float m_shapeAnglex, m_shapeAngley, m_shapeAnglez;
    float m_shapeRotatex, m_shapeRotatey, m_shapeRotatez;

};

#endif // SCENELR1_H_