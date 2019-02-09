//
// Created by kobarjan on 09.02.2019.
//

#ifndef TESTIGINTEENGINE_TEXTURE_H
#define TESTIGINTEENGINE_TEXTURE_H

#include <iostream>
#include <glad/glad.h>

enum TexturesTypes{
    PNG,
    JPG
};

class Texture {
public:
    Texture(const char *texturePath,TexturesTypes type);
    void bind();
    GLuint getID();
private:
    GLuint ID;
};


#endif //TESTIGINTEENGINE_TEXTURE_H
