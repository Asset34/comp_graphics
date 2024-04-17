#ifndef CONTROLLABLE_H_
#define CONTROLLABLE_H_

class Controllable {
public:
    virtual ~Controllable() {};

    virtual void control(int controlId) = 0;
    virtual void receiveValue(int valueId, int sendValue) {};
    virtual void receiveValue(int valueId, float sendValue) {};
    virtual void receiveValue(int valueId, bool sendValue) {};
    virtual void sendValue(int valueId, int &receiver) {};
    virtual void sendValue(int valueId, float &receiver) {};
    virtual void sendValue(int valueId, bool &receiver) {};

    virtual bool changed() = 0;
    virtual void changeAck() = 0; // Acknowledged

};


#endif // CONTROLLABLE_H_