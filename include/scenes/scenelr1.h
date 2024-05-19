#ifndef SCENELR1_H_
#define SCENELR1_H_

#include "interfaces/controllable.h"
#include "scenes/scene3d.h"
#include "objects/shape3d.h"
#include "objects/line3d.h"

#include <list>
#include <vector>

class SceneLR1 : public Scene3D, public Controllable {
public:
    SceneLR1();
    ~SceneLR1() {};

    void set(int vid, float value) override;
    void set(int vid, const float values[]) override;
    void get(int vid, float &receiver) override;
    void get(int vid, float receiver[]) override;

    void control(int cmd) override;
    bool updated() override;
    void updateAck() override;
    virtual const std::list<int> &getUpdateList();

private:
    void buildShape();
    void buildLine();

    enum Commands {
        CMD_SHAPE_SET = 0,
        CMD_LINE_BEGIN_SET = 1,
        CMD_LINE_END_SET = 2,
        CMD_ROTATE = 3
    };

    enum ValueIds {
        VID_SHAPE_POS = 0,
        VID_LINE_BEGIN_POS = 1,
        VID_LINE_END_POS = 2,
        VID_ROTATION_ANGLE = 3
    };

    Shape3D m_shape;
    Line3D m_line;
    
    // Control values
    vec3 m_shapePos;
    vec3 m_lineBeginPos, m_lineEndPos;
    float m_rotationAngle;
    bool m_updated;
    std::list<int> m_updateList;

};

#endif // SCENELR1_H_