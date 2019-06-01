#include "Mesh.h"
#include <GL/glew.h>
#include "File.h"

Mesh::Mesh(std::string filename) : parser(std::make_unique<ObjFileParser>(std::make_unique<File>(filename)))
{
    // Get the Data for the mesh.
    parser->Parse(vertices.get(), texels.get(), normals.get(), idxVertices.get(), idxTexels.get(), idxNormals.get());

    int attribPtrID = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * (vertices->size() + normals->size()) + sizeof(glm::vec2) * texels->size(), NULL, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * (idxVertices->size() + idxNormals->size() +  idxTexels->size()), NULL, GL_STATIC_DRAW);

    //Vertices
    glBufferSubData(GL_ARRAY_BUFFER,            0, sizeof(glm::vec3) * vertices->size() , &(*vertices)[0]);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,    0, sizeof(int) * idxVertices->size()    , &(*idxVertices)[0]);

    glEnableVertexAttribArray(attribPtrID);
    glVertexAttribPointer(attribPtrID, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void *)0);

    ++attribPtrID;
    if (!texels->empty())
    {

        size_t offsetTexelsData        = sizeof(glm::vec3) * vertices->size();
        size_t offsetTexelsIndices     = sizeof(int)       * idxVertices->size();

        glBufferSubData(GL_ARRAY_BUFFER,            offsetTexelsData,       sizeof(glm::vec2) * texels->size(),       &(*texels)[0]);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER,    offsetTexelsIndices,    sizeof(int)       * idxTexels->size(),    &(*idxTexels)[0]);

        glEnableVertexAttribArray(attribPtrID);
        glVertexAttribPointer(attribPtrID, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void *) offsetTexelsData);
    }

    ++attribPtrID;
    if (!normals->empty())
    {

        size_t offsetNormalsData       = sizeof(glm::vec3) *  vertices->size()    + sizeof(glm::vec2)   * texels->size();
        size_t offsetNormalsIndices    = sizeof(int)       *  idxVertices->size() + sizeof(int)         * idxTexels->size();

        glBufferSubData(GL_ARRAY_BUFFER,         offsetNormalsData,         sizeof(glm::vec3)   * normals->size(),      &(*normals)[0]);
        glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, offsetNormalsIndices,      sizeof(int)         * idxNormals->size(),   &(*idxNormals)[0]);
        glEnableVertexAttribArray(attribPtrID);
        glVertexAttribPointer(attribPtrID, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*) offsetNormalsData);
    }
   
    glBindVertexArray(0); 
}

Mesh::~Mesh(void)
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}


void Mesh::Render(void)
{
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, idxVertices->size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}