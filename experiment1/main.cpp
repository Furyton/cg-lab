#include <math.h>

#include "header/shader.hpp"
#include "header/frame.hpp"
#include "header/attribute.hpp"
#include "header/transformers.hpp"

#include <stdio.h>

#define V 500
#define DATA_PATH "./experiment1/points.data"

int n;

int point_num;

float vertices[V];


int main() {

    MyWindow window;

    if (window.init_window(800, 600)) {
        return -1;
    }

    Shader shader("./experiment1/shaders/shader.vs", "./experiment1/shaders/shader.fs");

    Attribute attr = Attribute();

    Transformers transformer;

    freopen(DATA_PATH, "r", stdin);

    std::cin>>n; // n * 3 * 3 point data

    point_num = n * 9;

    for (int i = 0; i < point_num; i++) {
        std::cin>>vertices[i];
    }

    attr.set_vertices(point_num * 4, vertices);
    
    attr.add_attr(0, 3);
    // attr.add_attr(1, 2);

    attr.build(GL_STATIC_DRAW);

    transformer.reset_acc_rotate();
    transformer.reset_acc_trans();

    while(!window.should_close()) {
        window.process_input(transformer);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float t = (float)glfwGetTime();

        shader.use();
        
        attr.activate();

        shader.setVec3("offset_color", glm::vec3(t, t, t));

        transformer.start();
        transformer.model_apply_acc_trans();
        transformer.model_apply_acc_rotate();

        transformer.view_trans(0.0f, 0.0f, -3.0f);
        transformer.apply_on_shader(shader);
        shader.setFloat("rate", 1.0);

        glDrawArrays(GL_TRIANGLES, 0, point_num);

        Transformers b(transformer);

        float repeat_0_1 = sin(t) * 0.5 + 0.5;
        float radius = repeat_0_1 * 0.5;

        b.model_trans(1.0f, 0.0f, 0.0f);
        b.model_trans(-0.5f, -0.5f, 0.0f);
        b.model_rotate(-radius, 0.0f, 0.0f, 1.0f);
        b.model_trans(0.5f, 0.5f, 0.0f);

        b.apply_on_shader(shader);
        shader.setFloat("rate", 1.0);

        glDrawArrays(GL_TRIANGLES, 0, point_num);

        attr.deactivate();

        window.swap_buffers();
        window.polling_events();
    }

    attr.destroy();

    window.close();

    return 0;
}