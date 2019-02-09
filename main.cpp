//#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <sstream>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
//#include <include/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"


void FrameBufferViewPort(GLFWwindow* window, int width, int height);

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(1280,720,"69", nullptr,nullptr);
    if(window== nullptr){
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window,FrameBufferViewPort);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST);

    auto *defaultshader = new Shader("resources/shaders/vertex.glsl","resources/shaders/fragment.glsl");

    //load models
    float vertices[] = {
            // positions        // texture coords
            0.5f,  0.5f, 0.0f,     1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,     0.0f, 1.0f  // top left
    };
    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int vao,vbo,ebo;
    glGenVertexArrays(1,&vao);
    glGenBuffers(1,&vbo);
    glGenBuffers(1,&ebo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER,vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),vertices,GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices),indices,GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,5 * sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    auto texture = new Texture("resources/textures/wall.jpg",JPG);


    glm::mat4 projection = glm::perspective(glm::radians(45.0f),(float)1280/720,0.1f,100.0f);

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view,glm::vec3(0.0f,0.0f,-3.0f));

    //glm::mat4

    defaultshader->use();
    glUniformMatrix4fv(glGetUniformLocation(defaultshader->getID(),"projection"),1,GL_FALSE,glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(defaultshader->getID(),"view"),1,GL_FALSE,glm::value_ptr(view));

    //glUniform1i(glGetUniformLocation(defaultshader->getID(),"image"),0);
    while(!glfwWindowShouldClose(window)){
        //input
        glClearColor(0.3f,0.3f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 trans = glm::mat4(1.0f);
        trans = glm::translate(trans,glm::vec3(0.5f,-0.5f,-5.0f));
        trans = glm::rotate(trans,(float)glfwGetTime(),glm::vec3(0.0f,0.0f,1.0f));

        //bind texture
        glActiveTexture(GL_TEXTURE0);
        texture->bind();
        //render
        defaultshader->use();

        glUniformMatrix4fv(glGetUniformLocation(defaultshader->getID(),"model"),1,GL_FALSE,glm::value_ptr(trans));

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES,sizeof(indices),GL_UNSIGNED_INT,0);
        //swap
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1,&vao);
    glDeleteBuffers(1,&vbo);
    glDeleteBuffers(1,&ebo);

    glfwTerminate();

    return 0;
}

void FrameBufferViewPort(GLFWwindow* window, int width, int height){
    glViewport(0,0,width,height);
}