#ifndef CONTROLLABLE_H_
#define CONTROLLABLE_H_

#include <list>

class Controllable {
public:
    virtual ~Controllable() {};

    virtual void control(int cmd) = 0;

    virtual void set(int id, int value)   {};
    virtual void set(int id, float value) {};
    virtual void set(int id, bool value)  {};

    virtual void get(int id, int &receiver)   {};
    virtual void get(int id, float &receiver) {};
    virtual void get(int id, bool &receiver)  {};

    virtual bool updated() = 0;
    virtual void updateAck() = 0; // Ack = Acknowledged
    virtual std::list<int> getUpdateList() = 0;

};


#endif // CONTROLLABLE_H_