#ifndef CONTROLLABLE_H_
#define CONTROLLABLE_H_

#include <list>
#include <vector>

class Controllable {
public:
    virtual ~Controllable() {};

    virtual void control(int cmd) = 0;

    virtual void set(int vid, int value)   {};
    virtual void set(int vid, float value) {};
    virtual void set(int vid, bool value)  {};
    virtual void set(int vid, const int values[]) {};
    virtual void set(int vid, const float values[]) {};
    virtual void set(int vid, const bool values[]) {};

    virtual void get(int vid, int &receiver)   {};
    virtual void get(int vid, float &receiver) {};
    virtual void get(int vid, bool &receiver)  {};
    virtual void get(int vid, int receiver[]) {};
    virtual void get(int vid, float receiver[]) {};
    virtual void get(int vid, bool receiver[]) {};

    virtual bool updated() = 0;
    virtual void updateAck() = 0; // Ack = Acknowledged
    virtual const std::list<int> &getUpdateList() = 0;

};


#endif // CONTROLLABLE_H_