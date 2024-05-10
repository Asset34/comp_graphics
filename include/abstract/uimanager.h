#ifndef UIMANAGER_H_
#define UIMANAGER_H_

class UiManager {
public:
    virtual ~UiManager() {};
    virtual void manage() = 0;
    virtual void update() = 0;

};

#endif // UIMANAGER_H_