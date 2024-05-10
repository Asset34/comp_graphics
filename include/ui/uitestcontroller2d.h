#ifndef UITESTCONTROLLER2D_H_
#define UITESTCONTROLLER2D_H_

#include "uiscenecontroller2d.h"

class UiTestController2D : public UiSceneController2D {
public:
    UiTestController2D(GLFWwindow *w = nullptr, bool manageContext = false);
    virtual ~UiTestController2D();

protected:
    void initFromControllable() override {};
    void updateFromControllable() override {};
    void control() override {};

    void renderUi() override {};

private:

        
};

#endif // UITESTCONTROLLER2D_H_