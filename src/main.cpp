#include <iostream>

#include "window.h"

int main() {
    Window w("Window test", 800, 600);

    w.open();
    w.draw();

    return 0;
}