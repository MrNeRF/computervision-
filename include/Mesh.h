#ifndef MESH_H
#define MESH_H

#include "ObjFileParser.h"
#include <memory>
#include <vector>
#include <string>

#define GLM_FORCE_CXX14
#include <glm/glm.hpp>

class Mesh
{
public:
    Mesh(std::string filename);
    ~Mesh(void);
    void Render();

private:
    unsigned int VAO; // VertexArrayObject
    unsigned int VBO; // VertexBufferObject
    unsigned int EBO; // ElemebtBufferObject

    std::unique_ptr<ObjFileParser> parser;

    std::unique_ptr<std::vector<glm::vec3>> vertices    = std::make_unique<std::vector<glm::vec3>>();
    std::unique_ptr<std::vector<glm::vec2>> texels      = std::make_unique<std::vector<glm::vec2>>();
    std::unique_ptr<std::vector<glm::vec3>> normals     = std::make_unique<std::vector<glm::vec3>>();

    std::unique_ptr<std::vector<int>> idxVertices   = std::make_unique<std::vector<int>>();
    std::unique_ptr<std::vector<int>> idxTexels     = std::make_unique<std::vector<int>>();
    std::unique_ptr<std::vector<int>> idxNormals    = std::make_unique<std::vector<int>>();
};

#endif