#ifndef TRANSFORMERS_H
#define TRANSFORMERS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "shader.hpp"
#include "smoothRotator.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Status {
    FREE, FIRST, SECOND, ROTATING, FINISHED
};

class Transformers {
private:
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    glm::vec3 accumulate_trans = glm::vec3(0.0f, 0.0f, 0.0f);

    glm::mat4 accumulate_rotate = glm::mat4(1.0f);

    Status status = FREE;

    glm::mat4 rotation_0, rotation_1;
    glm::vec3 trans_0, trans_1;

    SmoothRotator smoothRotator;

public:

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

    void head_to_next_status();

    glm::mat4& get_rotation_0();
    glm::vec3& get_trans_0();
    glm::mat4& get_rotation_1();
    glm::vec3& get_trans_1();

    Status get_status();
};

#endif