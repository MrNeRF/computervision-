#ifndef MESH_H
#define MESH_H

#include "ObjFileParser.h"
#include "Vertex.h"
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
    std::unique_ptr<std::vector<Vertex>> vertices = std::make_unique<std::vector<Vertex>>();
    std::unique_ptr<std::vector<int>> indices = std::make_unique<std::vector<int>>();
};

#endif