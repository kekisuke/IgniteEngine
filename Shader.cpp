//
// Created by kobarjan on 07.02.2019.
//

#include "Shader.h"

Shader::Shader(const char *vertexShaderpath,const char* fragmentShaderpath,const char* geometryShaderpath) {
    std::stringstream vertexS,fragmentS;
    std::ifstream ver(vertexShaderpath),frag(fragmentShaderpath);
    vertexS << ver.rdbuf();
    fragmentS << frag.rdbuf();
    std::string v = vertexS.str(),f=fragmentS.str();
    const char *vertexShaderSource=v.c_str(),*fragmentShaderSource=f.c_str();
    std::cout << vertexShaderSource << "\n" << fragmentShaderSource << "\n";
    ver.close();
    frag.close();
    unsigned int vertex=glCreateShader(GL_VERTEX_SHADER),fragment=glCreateShader(GL_FRAGMENT_SHADER),geometry;
    this->ID = glCreateProgram();
    glShaderSource(vertex,1,&vertexShaderSource,nullptr);
    glCompileShader(vertex);
    this->checkErrors(vertex,"VERTEX");

    glShaderSource(fragment, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragment);
    this->checkErrors(fragment,"FRAGMENT");

    if(geometryShaderpath!= nullptr){
        std::stringstream gS;
        std::ifstream geo(geometryShaderpath);
        gS << geo.rdbuf();
        std::string g=gS.str();
        const char *geometryShaderSource = g.c_str();
        geo.close();
        geometry=glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(geometry,1,&geometryShaderSource, nullptr);
        glCompileShader(geometry);
        this->checkErrors(geometry,"GEOMETRY");
    }

    glAttachShader(this->ID,vertex);
    glAttachShader(this->ID,fragment);
    if(geometryShaderpath!= nullptr){
        glAttachShader(this->ID,geometry);
    }
    glLinkProgram(this->ID);
    this->checkErrors(this->ID,"PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    if(geometryShaderpath!= nullptr){
        glDeleteShader(geometry);
    }
}

void Shader::use() {
    glUseProgram(this->ID);
}

void Shader::SetFloat(const GLchar *name, GLfloat value) {

    glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetInt(const GLchar *name, GLint value) {

    glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::SetVector2f(const GLchar *name,const glm::vec2 &value) {

    glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::SetVector3f(const GLchar *name, const glm::vec3 &value) {

    glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::SetVector4f(const GLchar *name, const glm::vec4 &value) {

    glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::SetMat4f(const GLchar *name, const glm::mat4 &value) {

    glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, GL_FALSE, glm::value_ptr(value));
}

GLuint Shader::getID() {
    return this->ID;
}

void Shader::checkErrors(GLuint obj, std::string type) {
    GLint succes;
    GLchar log[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(obj, GL_COMPILE_STATUS, &succes);
        if (!succes) {
            glGetShaderInfoLog(obj, 1024, NULL, log);
            std::cout << " error.shader: compile error: type: " << type << "\n" << log << "\n ---------------------------------------------------------------------" << std::endl;
        }
    }
    else {
        glGetProgramiv(obj, GL_LINK_STATUS, &succes);
        if (!succes) {
            glGetProgramInfoLog(obj, 1024, NULL, log);
            std::cout << " error.shader: link error: type: " << type << "\n" << log << "\n ---------------------------------------------------------------------" << std::endl;
        }
    }
}
