#ifndef SCENELR3_H_
#define SCENELR3_H_

#include "scenes/scene3d.h"
#include "interfaces/controllable.h"


class SceneLR3 : public Scene3D, public Controllable {
public:
    SceneLR3();
    ~SceneLR3() {};
    
    // void set(int vid, int value) override;
    // void set(int vid, float value) override;
    // void set(int vid, const float values[]) override;
    // void set(int vid, bool value) override;
    // void get(int vid, int &receiver) override;
    // void get(int vid, float &receiver) override;
    // void get(int vid, bool &receiver) override;
    // void get(int vid, float receiver[]) override;

    void control(int cmd) override;
    bool updated() override;
    void updateAck() override;
    const std::list<int> &getUpdateList() override;

private:

    enum Commands {
    };

    enum ValueIds {
    };

    // Objects
    
    // Control values
    std::list<int> m_updateList;

};

#endif // SCENELR3_H_