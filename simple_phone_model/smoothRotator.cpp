#include "header/smoothRotator.hpp"

bool SmoothRotator::calc() {
    T += 0.0075f;
    
    std::cout<<std::endl<<"t: "<<T<<std::endl;

    if (fabs(T - 1.0f) < 1e-6 || T > 1.0f) return true;

    q_t = (1-T) * q_0 + T * q_1;
    q_t = q_t / glm::sqrt(q_t.w * q_t.w + q_t.x * q_t.x + q_t.y * q_t.y + q_t.z * q_t.z);
    trans_t = (1-T) * trans_0 + T * trans_1;

    return false;
}

void SmoothRotator::load_bullet(glm::mat4& rotation, glm::vec3& trans) {
    q_0 = q_t = glm::quat_cast(glm::mat3(rotation));
    trans_0 = trans_t = glm::vec3(trans);

    T = 0.0f;
}

void SmoothRotator::set_target(glm::mat4& rotation, glm::vec3& trans) {
    q_1 = glm::quat_cast(glm::mat3(rotation));
    trans_1 = glm::vec3(trans);

    T = 0.0f;
}

bool SmoothRotator::rotation_terminated() {
    return calc();
}

glm::mat4 SmoothRotator::get_current_rotation() {
    return glm::mat4_cast(q_t);
}
glm::vec3& SmoothRotator::get_current_translation() {
    return trans_t;
}
