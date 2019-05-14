#ifndef OBJECT_FILE_PARSER
#define OBJECT_FILE_PARSER

#include "File.h"
#include <string>
#include <memory>
#include <vector>
#include "Vec2.h"
#include "Vec3.h"
#define GLM_FORCE_CXX14
#include <glm/glm.hpp>


class ObjFileParser
{
    public:
        explicit ObjFileParser(std::unique_ptr<File> &up_fileToParse) : m_upFileToParse(std::move(up_fileToParse)){};
        void Parse(void);
        void GetOpenGLData(std::vector<glm::vec3> &vertGL, std::vector<glm::vec2> &texGL, std::vector<glm::vec3> &normGL);
        
        std::vector<Vec3f> GetVertices(void) const {return vertices;};
        std::vector<Vec2f> GetTexels(void) const {return texels;};
        std::vector<Vec3f> GetNormals(void) const {return normals;};
    private:
        void tokenize(std::string &line, char delim, std::vector<std::string> &tokens);

    private:
       std::unique_ptr<File> m_upFileToParse;
       std::vector<Vec3f> vertices;
       std::vector<Vec2f> texels;
       std::vector<Vec3f> normals;
       
	   std::vector<int> index_vert;
	   std::vector<int> index_text;
	   std::vector<int> index_norm;
};

#endif
