
#include "shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath){
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    const char* vertex_shader = readShaderFromFile(vertexPath).c_str();

    glShaderSource(vs, 1, &vertex_shader, NULL);
    glCompileShader(vs);
    checkCompileErrors(vs,"VERTEX");

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragment_shader = readShaderFromFile(fragmentPath).c_str();
    glShaderSource(fs, 1, &fragment_shader, NULL);
    glCompileShader(fs);
    checkCompileErrors(fs,"FRAGMENT");

    // definiraj sjencarski program
    ID = glCreateProgram();
    glAttachShader(ID, fs);
    glAttachShader(ID, vs);
    glLinkProgram(ID);
    checkCompileErrors(ID,"PROGRAM");
}


std::string Shader::readShaderFromFile(const char *filePath) {
    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if(!fileStream.is_open()) {
        std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
        return "";
    }

    std::string line = "";
    while(!fileStream.eof()) {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();
    return content;
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
    {
        int success;
        char infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
            }
        }
    }


void Shader::setMat4(const std::string &name, const glm::mat4 &mat) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}


void Shader::setVec3(const std::string &name, const glm::vec3 &value) const {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void Shader::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(ID,name.c_str()),value);
}

void Shader::setInt(const std::string &name, GLuint value) const{
    glUniform1i(glGetUniformLocation(ID,name.c_str()),value);
}
