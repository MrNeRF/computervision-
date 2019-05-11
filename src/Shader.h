#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <GL/glew.h>  
#include <GLFW/glfw3.h>

class Shader
{
    public:
        unsigned int ID;

        Shader(const char* vertexPath, const char* fragmentPath)
        {
            std::string vertexCode;
            std::string fragmentCode;
            std::ifstream vShaderFile;
            std::ifstream fShaderFile;

            vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            
            try
            {
                vShaderFile.open(vertexPath);
                fShaderFile.open(fragmentPath);
                std::stringstream vShaderStream, fShaderStream;

                vShaderStream << vShaderFile.rdbuf();
                fShaderStream << fShaderFile.rdbuf();

                vShaderFile.close();
                fShaderFile.close();
                
                vShaderFile.close();
                fShaderFile.close();

                vertexCode = vShaderStream.str();
                fragmentCode = fShaderStream.str();
            }
            catch(const std::ifstream::failure& e)
            {
                std::cerr << "ERROR: Shader file not successfully read" << std::endl;
            }

            const char *vSahderCode = vertexCode.c_str();
            const char *fShaderCode = fragmentCode.c_str();
            
            unsigned int vertex, fragment;
            vertex = glCreateShader(GL_VERTEX_SHADER);


        }
};

#endif