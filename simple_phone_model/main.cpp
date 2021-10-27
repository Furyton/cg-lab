#include <math.h>

#include "header/shader.hpp"
#include "header/frame.hpp"
#include "header/model.hpp"
#include "header/transformers.hpp"

#include <stdio.h>

#define V 500
char* DATA_PATH = "./data/nanosuit/nanosuit.obj";

int main() {
    MyWindow window;

    if (window.init_window(800, 600)) {
        return -1;
    }

    Shader shader("./simple_phone_model/shaders/shader.vs", "./simple_phone_model/shaders/shader.fs");

    Model model(DATA_PATH);

    Transformers transformer;

    transformer.reset_acc_rotate();
    transformer.reset_acc_trans();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); 

    while(!window.should_close()) {
        window.process_input(transformer);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        float t = (float)glfwGetTime();

        shader.use();
        
        shader.setVec3("offset_color", glm::vec3(t, t, t));

        transformer.start();
        transformer.model_apply_acc_trans();
        transformer.model_apply_acc_rotate();

        transformer.view_trans(0.0f, 0.0f, -3.0f);
        transformer.apply_on_shader(shader);
        shader.setFloat("rate", 1.0);

        model.draw(shader);

        window.swap_buffers();
        window.polling_events();
    }

    model.destroy();

    window.close();

    return 0;
}