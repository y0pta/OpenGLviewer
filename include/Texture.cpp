//
// Created by Liza on 3/14/2023.
//

#include "Texture.h"

#ifndef STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"
#endif
#include <iostream>

bool Texture::load(const std::string& loadPath){
    // Gen textures
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    // texture wrapping setup
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // filtration
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load textures
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(loadPath.c_str(), &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        initialized = true;
    }
    else{
        std::cout << "Failed to load texture" << std::endl;
        initialized = false;
    }
    stbi_image_free(data);

    return initialized;
}

Texture::Texture(const std::string& loadPath) {
    initialized = load(loadPath);
}

Texture& Texture::instance(TextureType type) {
    static Texture smile("../samples/textures/awesomeface.png");
    static Texture woodenContainer("../samples/textures/wooden_container.jpg");

    switch (type) {
        case eSmile:
            return smile;
        case eWoodenBox:
            return woodenContainer;
        default:
            return smile;
    }
}