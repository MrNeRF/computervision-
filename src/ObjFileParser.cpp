#include "ObjFileParser.h"
#include <fstream>
#include <algorithm>


void ObjFileParser::Parse(std::vector<glm::vec3> *vertices,
                        std::vector<glm::vec2> *texels, 
                        std::vector<glm::vec3> *normals,
                        std::vector<int> *idxVertices,
                        std::vector<int> *idxTexels,
                        std::vector<int> *idxNormals)

{
    std::string buffer;
    upFileToParse->GetContents(buffer);

    std::istringstream iss(buffer);

    std::string line;

    for (std::string line; std::getline(iss, line); )
    {
        std::vector<std::string> tokens;
        tokenize(line, ' ', tokens);

        if(tokens.at(0).compare("v") == 0 && tokens.size() == 4)
        {
            //Vertex
            vertices->emplace_back(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
        }
        else if (tokens.at(0).compare("vt") == 0 && tokens.size() == 3)
        {
            // texture coordinates
            texels->emplace_back(std::stof(tokens[1]), std::stof(tokens[2]));
        }
        else if (tokens.at(0).compare("vn") == 0 && tokens.size() == 4)
        {
            normals->emplace_back(std::stof(tokens[1]), std::stof(tokens.at(2)), std::stof(tokens.at(3)));
        }
        else if (tokens.at(0).compare("f") == 0 && tokens.size() == 4 )
		{
			for (int i = 1; i < 4; ++i)
			{
				std::vector<std::string> subTokens;
				tokenize(tokens.at(i), '/', subTokens);

                // Indices start at 1 that is why we have to subtract 1
                idxVertices->push_back(std::stoi(subTokens[0]) - 1);
                idxTexels->push_back(std::stoi(subTokens[1]) - 1);
                idxNormals->push_back(std::stoi(subTokens[2]) - 1);
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


