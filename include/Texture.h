//
// Created by Liza on 3/14/2023.
//

#ifndef OPENGL_PRJ_TEXTURE_H
#define OPENGL_PRJ_TEXTURE_H

#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

class Texture {
    public:
        enum TextureType{
            eSmile,
            eWoodenBox
        };

    public:
        Texture(const std::string& loadPath);
        ~Texture() {};

        static Texture& instance(TextureType type);
        void bind(GLenum slot = GL_TEXTURE0) const
            { glActiveTexture(slot); glBindTexture(GL_TEXTURE_2D, id); }

    protected:
        unsigned int id;
};


#endif //OPENGL_PRJ_TEXTURE_H
