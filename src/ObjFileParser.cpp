#include "ObjFileParser.h"
#include <fstream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <map>


void ObjFileParser::Parse(void)
{
    std::string buffer;
    m_upFileToParse->GetContents(buffer);

    std::istringstream iss(buffer);

    std::string line;

    for (std::string line; std::getline(iss, line); )
    {
        std::vector<std::string> tokens;
        tokenize(line, ' ', tokens);

        if(tokens.at(0).compare("v") == 0 && tokens.size() == 4)
        {
            //Vertex
            vertices.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
        }
        else if (tokens.at(0).compare("vt") == 0 && tokens.size() == 3)
        {
            // texture coordinates
            texels.emplace_back(std::stof(tokens[1]), std::stof(tokens[2]));
        }
        else if (tokens.at(0).compare("vn") == 0 && tokens.size() == 4)
        {

            normals.emplace_back(std::stof(tokens[1]), std::stof(tokens.at(2)), std::stof(tokens.at(3)));
        }
    }
}


void ObjFileParser::tokenize(std::string &line, char delim, std::vector<std::string> &tokens)
{
    auto start = find(cbegin(line), cend(line), delim);
    tokens.push_back(std::string(cbegin(line), start));

    while (start != cend(line)) 
    {
        const auto finish = find(++start, cend(line), delim);

        tokens.push_back(std::string(start, finish));
        start = finish;
    }
}


void ObjFileParser::GetOpenGLData(std::vector<glm::vec3> &vertGL, std::vector<glm::vec2> &texGL, std::vector<glm::vec3> &normGL)
{
    for(size_t i = 0; i < vertices.size(); ++i)
    {
        vertGL.push_back(glm::vec3(vertices[i].x, vertices[i].y, vertices[i].z));
    }

    for(size_t i = 0; i < texels.size(); ++i)
    {
        texGL.push_back(glm::vec2(texels[i].x, texels[i].y));
    }

    for(size_t i = 0; i < normals.size(); ++i)
    {
        normGL.push_back(glm::vec3(normals[i].x, normals[i].y, normals[i].z));
    }

}
