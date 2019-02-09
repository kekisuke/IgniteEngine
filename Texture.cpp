//
// Created by kobarjan on 09.02.2019.
//

#define STB_IMAGE_IMPLEMENTATION
#include <include/stb_image.h>

#include "Texture.h"

Texture::Texture(const char *texturePath,TexturesTypes type) {
    glGenTextures(1,&this->ID);
    this->bind();
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    int width,height,nrChannel;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(texturePath,&width,&height,&nrChannel,0);
    if(data){
        if(type==JPG) glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
        else if(type==PNG) glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,data);
        glGenerateMipmap(GL_TEXTURE_2D);

    } else {
        std::cout << "failed loading texture\n";
    }
    //loop
    stbi_image_free(data);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D,this->ID);
}

GLuint Texture::getID() {
    return this->ID;
}
