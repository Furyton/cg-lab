#ifndef SMOOTHROTATOR_H
#define SMOOTHROTATOR_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <iostream>

// input target rotation matrix, translation matrix
// ouput rotation matrix, translation matrix at time step t
const float delta_t = 0.0075f;

class SmoothRotator {
private:
    float T = 0.0f;

    glm::qua<float> q_1;
    glm::vec3 trans_1;

    glm::qua<float> q_t;
    glm::vec3 trans_t;

    glm::qua<float> q_0;
    glm::vec3 trans_0;

    bool calc();
public:
    bool rotation_terminated();
    
    void load_bullet(glm::mat4& rotation, glm::vec3& trans);
    void set_target(glm::mat4& rotation, glm::vec3& trans);

    glm::mat4 get_current_rotation();
    glm::vec3& get_current_translation();
};

#endif