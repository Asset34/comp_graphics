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

    float m_shapeMovex, m_shapeMovey, m_shapeMovez;
    float m_shapeAnglex, m_shapeAngley, m_shapeAnglez;
    float m_shapeRotatex, m_shapeRotatey, m_shapeRotatez;

    float m_lineBeginx, m_lineBeginy, m_lineBeginz;
    float m_lineEndx, m_lineEndy, m_lineEndz;

};

#endif // SCENELR1_H_