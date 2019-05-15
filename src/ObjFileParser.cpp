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
            vertices.emplace_back(std::stof(tokens[1])*0.5f, std::stof(tokens[2])*0.5f, std::stof(tokens[3])*0.5);
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
        else if (tokens.at(0).compare("f") == 0 && tokens.size() == 4 )
		{
			for (int i = 1; i < 4; ++i)
			{
				std::vector<std::string> subTokens;
				tokenize(tokens.at(i), '/', subTokens);

                index_vert.push_back(std::stoi(subTokens[0]));
                index_text.push_back(std::stoi(subTokens[1]));
                index_norm.push_back(std::stoi(subTokens[2]));
			}
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

void ObjFileParser::GetVerticesOpenGL(std::vector<glm::vec3> &vertGL, std::vector<int> &indices)
{
    for(size_t i = 0; i < index_vert.size(); ++i)
    {
        vertGL.push_back(glm::vec3(vertices[index_vert[i] - 1].x, vertices[index_vert[i] - 1].y, vertices[index_vert[i] - 1].z));
    }

    indices = index_vert;

    // for(size_t i = 0; i < texels.size(); ++i)
    // {
    //     texGL.push_back(glm::vec2(texels[index_text[i]].x, texels[index_text[i]].y));
    // }

    // for(size_t i = 0; i < normals.size(); ++i)
    // {
    //     normGL.push_back(glm::vec3(normals[index_norm[i]].x, normals[index_norm[i]].y, normals[index_norm[i]].z));
    // }

}


