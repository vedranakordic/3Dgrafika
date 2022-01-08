#pragma once
// OpenGL libs
#include <GL/glew.h> // GLEW za upravljanje kontekstom
#include <GLFW/glfw3.h> // GLFW pomocna biblioteka
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/normal.hpp>

// input-output
#include <stdio.h>
#include <iostream>
#include <fstream>


// std data structures
#include <vector>  // STD lib




class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char* vertexPath, const char* fragmentPath);
    // use/activate the shader
    void use();

    // postavljanje uniformnih varijabli
    void setMat4(const std::string& name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setFloat(const std::string &name, float x) const;
    void setInt(const std::string &name, GLuint value) const;

protected:
    // read from file
    std::string readShaderFromFile(const char *filePath);
    // check compilation errors
    void        checkCompileErrors(unsigned int shader, std::string type);
};




