#include "header/transformers.hpp"

void Transformers::start() {
    model = glm::mat4(1.0f);
    view = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
}
void Transformers::reset_acc_rotate() {
    accumulate_rotate = glm::mat4(1.0f);
}
void Transformers::reset_acc_trans() {
    accumulate_trans = glm::vec4(0.0f);
}

// rotate around the origin in local coodinate system
void Transformers::model_rotate(float radians, glm::vec3& axis) {
    model = glm::rotate(model, radians, glm::normalize(axis));
}
void Transformers::model_rotate(float radians, float x, float y, float z) {
    model = glm::rotate(model, radians, glm::normalize(glm::vec3(x, y, z)));
}

void Transformers::model_rotate(glm::mat4& r) {
    model = model * r;
}

void Transformers::model_trans(glm::vec3 &delta) {
    model = glm::translate(model, delta);
}
void Transformers::model_trans(float x, float y, float z) {
    model = glm::translate(model, glm::vec3(x, y, z));
}

void Transformers::model_apply_acc_rotate() {
    if (status == ROTATING) {
        model = model * smoothRotator.get_current_rotation();
    } else {
        model = model * accumulate_rotate;
    }
}
void Transformers::model_apply_acc_trans() {
    if (status == ROTATING) {
        model = glm::translate(model, smoothRotator.get_current_translation());
    } else {
        model = glm::translate(model, accumulate_trans);
    }
}

void Transformers::view_trans(glm::vec3& delta) {
    view = glm::translate(view, delta);
}
void Transformers::view_trans(float x, float y, float z) {
    view = glm::translate(view, glm::vec3(x, y, z));
}

void Transformers::projection_perspective() {

}

void Transformers::apply_on_shader(Shader &shader) {
    shader.setMat4("model", model);
    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
}

void Transformers::input_rotate(float radians, float x, float y, float z) {
    accumulate_rotate = glm::rotate(glm::mat4(1.0f), radians, glm::normalize(glm::vec3(x, y, z))) * accumulate_rotate;
}

void Transformers::input_rotate(float radians, glm::vec3& axis) {
    accumulate_rotate = glm::rotate(glm::mat4(1.0f), radians, glm::normalize(axis)) * accumulate_rotate;
}

void Transformers::input_rotate(glm::mat4& r) {
    accumulate_rotate = r * accumulate_rotate;
}

void Transformers::input_translate(float x, float y, float z) {
    accumulate_trans += glm::vec3(x, y, z);
}

void Transformers::input_translate(glm::vec3& delta) {
    accumulate_trans += delta;
}

float Transformers::get_acc_trans_norm() {
    // return 1.0f;

    float x = accumulate_trans[0], y = accumulate_trans[1], z = accumulate_trans[2];
    float len = glm::sqrt(x * x + y * y + z * z);

    if (len < 0.5f) return 1.0f;
    
    return len;

    // return accumulate_trans.length() < 1e-6f : 1.0f ? accumulate_trans.length();
}

void Transformers::head_to_next_status() {
    std::cout<<"from status: "<< status;
    if (status == FREE) {
        rotation_0 = glm::mat4(accumulate_rotate);
        trans_0 = glm::vec3(accumulate_trans);

        smoothRotator.load_bullet(rotation_0, trans_0);

        status = FIRST;
    } else if (status == FIRST) {
        rotation_1 = glm::mat4(accumulate_rotate);
        trans_1 = glm::vec3(accumulate_trans);

        smoothRotator.set_target(rotation_1, trans_1);

        status = SECOND;
    } else if (status == SECOND) {
        status = ROTATING;
    } else if (status == ROTATING) {
        if (smoothRotator.rotation_terminated())
            status = FINISHED;
    } else {
        reset_acc_rotate();
        reset_acc_trans();

        status = FREE;
    }

    std::cout<<" to: "<<status<<std::endl;
}

Status Transformers::get_status() {
    return status;
}

glm::mat4& Transformers::get_rotation_0() {
    return rotation_0;
}
glm::vec3& Transformers::get_trans_0() {
    return trans_0;
}
glm::mat4& Transformers::get_rotation_1() {
    return rotation_1;
}
glm::vec3& Transformers::get_trans_1() {
    return trans_1;
}