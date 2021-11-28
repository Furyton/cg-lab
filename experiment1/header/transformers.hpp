#ifndef TRANSFORMERS_H
#define TRANSFORMERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Transformers {
private:
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 accumulate_trans = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 accumulate_rotate = glm::mat4(1.0f);

public:
    Transformers(Transformers&);
    Transformers() {
        start();
        reset_acc_rotate();
        reset_acc_trans();
    }

    void start();
    void reset_acc_rotate();
    void reset_acc_trans();

    // rotate around the origin in local coodinate system
    void model_rotate(float radians, glm::vec3& axis);
    void model_rotate(float radians, float x, float y, float z);
    void model_rotate(glm::mat4& r);

    void model_trans(glm::vec3 &delta);
    void model_trans(float x, float y, float z);

    void model_apply_acc_rotate();
    void model_apply_acc_trans();

    void view_trans(glm::vec3 &delta);
    void view_trans(float x, float y, float z);

    void projection_perspective();

    void apply_on_shader(Shader &shader);

    void input_rotate(float radians, float x, float y, float z);
    void input_rotate(float radians, glm::vec3& axis);
    void input_rotate(glm::mat4& r);
    void input_translate(float x, float y, float z);
    void input_translate(glm::vec3 &delta);

    float get_acc_trans_norm();
};

#endif