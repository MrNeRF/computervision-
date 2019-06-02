#ifndef VERTEX_H
#define VERTEX_H

#define GLM_FORCE_CXX14
#include <glm/glm.hpp>


struct Vertex
{
    Vertex() : Vertex({0.0, 0.0, 0.0}, {0.0, 0.0}, {0.0, 0.0, 0.0}) {};
    Vertex(glm::vec3 pos): Vertex(pos, {0.0, 0.0}) {};; 
    Vertex(glm::vec3 pos, glm::vec3 norm) : Vertex(pos, {0.0, 0.0}, norm) {};
    Vertex(glm::vec3 pos, glm::vec2 tex) : Vertex(pos, tex, {0.0, 0.0, 0.0}) {};
    Vertex(glm::vec3 pos, glm::vec2 tex, glm::vec3 norm) : position(pos), texel(tex), normal(norm){};
    glm::vec3 position;
    glm::vec2 texel;
    glm::vec3 normal;
};

#endif