#include "Mesh.h"
#include <GL/glew.h>
#include <stddef.h>
#include "File.h"

Mesh::Mesh(std::string filename) : parser(std::make_unique<ObjFileParser>(std::make_unique<File>(filename)))
{
    // Get the Data for the mesh.
    parser->Parse(vertices.get(), indices.get());

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices->size(), &(*vertices)[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices->size(), &(*indices)[0], GL_STATIC_DRAW);

    // Position Coordinates
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, position));

    // Texture Coordinates
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *) offsetof(Vertex, texel));

    // Normal Coordinates
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, normal));

    glBindVertexArray(0); 
}

Mesh::~Mesh(void)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}


void Mesh::Render(void)
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices->size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}