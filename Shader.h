//
// Created by kobarjan on 07.02.2019.
//

#ifndef TESTIGINTEENGINE_SHADER_H
#define TESTIGINTEENGINE_SHADER_H

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>


class Shader {
public:
    Shader(const char* vertexShaderpath,const char* fragmentShaderpath,const char* geometryShaderpath= nullptr);
    void use();
    void SetFloat(const GLchar *name, GLfloat value);
    void SetInt(const GLchar *name, GLint value);
    void SetVector2f(const GLchar *name, const glm::vec2 &value);
    void SetVector3f(const GLchar *name, const glm::vec3 &value);
    void SetVector4f(const GLchar *name, const glm::vec4 &value);
    void SetMat4f(const GLchar *name, const glm::mat4 &value);
    GLuint getID();
private:
    GLuint ID;
    void checkErrors(GLuint obj, std::string type);
};


#endif //TESTIGINTEENGINE_SHADER_H
