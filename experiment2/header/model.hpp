#ifndef MODEL_H
#define MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include "shader.hpp"
#include "attribute.hpp"

#include <vector>
#include <string>
#include <iostream>

class Model {
public:
    Model(char *path) {
        loadModel(path);
    }
    void draw(Shader &shader);

    void destroy() {
        for (auto attr: attrs) {
            attr.destroy();
        }
    }

private:
    std::vector<Attribute> attrs;
    std::string directory;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Attribute processAttr(aiMesh *mesh, const aiScene *scene);
};

#endif