#include <math.h>

#include "header/frame.hpp"

#include <stdio.h>
#include <fstream>

int main() {
    MyWindow window;

    if (window.init_window(800, 600)) {
        return -1;
    }

    while(!window.should_close()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glVertex3f(0, 1, 0);
        glVertex3f(-1, 0, 0);
        glVertex3f(1, 0, 0);
        glEnd();

        window.swap_buffers();
        window.polling_events();
    }

    window.close();

    return 0;
}