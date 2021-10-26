#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <iostream>

const int MAX_BONE_INFLUENCE = 4;

struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;

    int m_BoneIDs[MAX_BONE_INFLUENCE];
    float m_Weights[MAX_BONE_INFLUENCE];
};

class Attribute {
private:
    unsigned int VBO, VAO, EBO;

    std::vector<unsigned int> indices;

    std::vector<struct Vertex> vertices;
    
    void build();    
    
    void activate();
    
    void deactivate();
    
public:
    Attribute(std::vector<struct Vertex> &vertices, std::vector<unsigned int> &indices);

    // usage: GL_STATIC_DRAW, GL_DYNAMIC_DRAW...
    void destroy();

    void draw();
};

#endif