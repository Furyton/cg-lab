#include <math.h>

#include "header/utils.hpp"
#include "header/shader.hpp"
#include "header/frame.hpp"
#include "header/attribute.hpp"
#include "header/transformers.hpp"

#include <stdio.h>
#include <fstream>

#define V 500
#define DATA_PATH "./experiment1/points.data"

int n;

int point_num;

// Vertex anchor[3] 
float anchor[3][3] = {{-0.5f, -0.5f, -0.5f}, 
                    {-0.125f, -0.5f, -0.125f},
                    {-0.25f, -0.25f, -0.25f}};

float z[3] = {1.0f, 0.25f, 0.5f};
float y[3] = {1.0f, 1.0f, 0.5f};
float x[3] = {1.0f, 0.25f, 0.5f};

void trans_it(Transformers curt, Transformers f, Shader& shader, Attribute& attr, glm::vec3 delta, glm::vec3 rotate_anchor, glm::vec3 rotate_axis, float radius, glm::vec3 color_offset) {
        attr.activate();

        shader.setVec3("offset_color", color_offset);

        curt.inherit(f);

        curt.model_trans(delta);
        curt.model_trans(rotate_anchor.operator*=(-1.0f));
        curt.model_rotate(radius, rotate_axis);
        curt.model_trans(rotate_anchor.operator*=(-1.0f));

        curt.apply_on_shader(shader);
        shader.setFloat("rate", 1.0);

        glDrawArrays(GL_TRIANGLES, 0, point_num);

        attr.deactivate();
}
void trans_it(Transformers curt, Transformers f, Shader& shader, Attribute& attr, glm::vec3 delta, glm::vec3 color_offset) {
        attr.activate();

        shader.setVec3("offset_color", color_offset);

        curt.inherit(f);

        curt.model_trans(delta);

        curt.apply_on_shader(shader);
        shader.setFloat("rate", 1.0);

        glDrawArrays(GL_TRIANGLES, 0, point_num);

        attr.deactivate();
}


int main() {

    MyWindow window;

    if (window.init_window(800, 600)) {
        return -1;
    }

    Shader shader("./experiment1/shaders/shader.vs", "./experiment1/shaders/shader.fs");

    Attribute attr[3];

    Transformers body, limb, head;

    point_num = 12 * 9;

    for (int i = 0; i < 3; i++ ){
        attr[i].set_vertices(point_num * 4, get_vertex(anchor[i], z[i], y[i], x[i]));

        attr[i].add_attr(0, 3);
        attr[i].build(GL_STATIC_DRAW);
    }


    while(!window.should_close()) {
        window.process_input(body);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float t = (float)glfwGetTime();

        shader.use();

        // body

        attr[0].activate();

        shader.setVec3("offset_color", glm::vec3(0., 0.25, 0.5));

        body.start();
        body.model_apply_acc_trans();
        body.model_apply_acc_rotate();

        body.view_trans(0.0f, 0.0f, -5.0f);
        body.apply_on_shader(shader);
        shader.setFloat("rate", 1.0);

        glDrawArrays(GL_TRIANGLES, 0, point_num);
        attr[0].deactivate();

        float repeat_0_1 = sin(t * 10) * 0.5 + 0.5;
        float radius = repeat_0_1 * 0.5;

        trans_it(limb, body, shader, attr[1], glm::vec3(x[0] / 2 + x[1] / 2, 0.0f, 0.0f), glm::vec3(x[1] / 2, -y[1] / 2, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), radius, glm::vec3(1, 0.75, 0.5));

        trans_it(limb, body, shader, attr[1], glm::vec3(-(x[0] / 2 + x[1] / 2), 0.0f, 0.0f), glm::vec3(-x[1] / 2, -y[1] / 2, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), -radius, glm::vec3(1, 0.75, 0.5));

        trans_it(limb, body, shader, attr[1], glm::vec3(x[1], -y[1], 0.0f), glm::vec3(0.0f, -y[1] / 2, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), radius, glm::vec3(1, 0.75, 0.5));
    
        trans_it(limb, body, shader, attr[1], glm::vec3(-x[1], -y[1], 0.0f), glm::vec3(0.0f, -y[1] / 2, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), -radius, glm::vec3(1, 0.75, 0.5));


        trans_it(head, body, shader, attr[2], glm::vec3(0.0f, y[2] / 2 + y[0] / 2, 0.0f), glm::vec3(0, 1, 1));

        window.swap_buffers();
        window.polling_events();
    }

    attr[0].destroy();
    attr[1].destroy();

    window.close();

    return 0;
}