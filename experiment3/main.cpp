#include <math.h>

#include "header/frame.hpp"

#include <stdio.h>
#include <fstream>

GLfloat ctrlpoints[4][3] = {
    { -2, -2, 0 }, { -2, 2, 0 }, { 2, -2, 0 }, { 2, 2, 0 }
};

int main() {
    MyWindow window;

    if (window.init_window(800, 600)) {
        return -1;
    }

    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    //打开开关——允许3维坐标控制点到参数点转换开关
    glEnable(GL_MAP1_VERTEX_3);
    glShadeModel(GL_FLAT);

    while(!window.should_close()) {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glLoadIdentity();
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.f);

        glm::mat4 m = projection * view * model;

        glLoadMatrixf(glm::value_ptr(m));
        glColor3f(1.0, 0.0, 0.0);
        //绘制连续线段
        glBegin(GL_LINE_STRIP);
        int i;
        //参数t或u取值为i/30，共计31个点
        for (i = 0; i <= 100; i++)
            glEvalCoord1f((GLfloat)i / 100.0);   //根据4个控制点坐标的参数化插值
        glEnd();

        glPointSize(5.0);
        glBegin(GL_POINTS);
        for (i = 0; i < 4; i++)
            glVertex3fv(&ctrlpoints[i][0]);
        glEnd();

        window.swap_buffers();
        window.polling_events();
    }

    window.close();

    return 0;
}