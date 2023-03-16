//
// Created by Liza on 3/16/2023.
//

#ifndef OPENGL_PRJ_PRIMITIVES_H
#define OPENGL_PRJ_PRIMITIVES_H

#include "Shader.h"
#include "Texture.h"
#include "Camera.h"


class Primitive{
    public:
        Primitive(glm::vec3 pos = glm::vec3(0.f, 0.f, 0.f), glm::quat q = glm::vec3(0, 0, 0)):
                origin(pos), q_origin(q){}
        ~Primitive(){}

        void setScale(float s) {scale = s;}
        void setOrigin(const glm::vec3& newOrigin) {origin = newOrigin;}
        void setRotation(const glm::quat& newRot) {q_origin = newRot;}
        virtual void render(Camera* cam) const = 0;

    protected:
        glm::vec3 origin;
        glm::quat q_origin;

        float scale = 1.0f;
};

class Axes : public Primitive{
    public:
        Axes();
        ~Axes() {};

        virtual void render(Camera* cam) const override;

    public:
        static bool initialized;

    protected:
        static void _init();

    protected:
        static unsigned int VBO;
        static unsigned int VAO;

        Shader& shader;
};

class TexturedCube : public Primitive{
public:
    TexturedCube();
    ~TexturedCube() {};

    virtual void render(Camera* cam) const;

    public:
        static bool initialized;

    protected:
        static void _init();

    protected:
        static unsigned int VBO;
        static unsigned int VAO;

        Texture& texture1;
        Texture& texture2;

        Shader& shader;
};

#endif //OPENGL_PRJ_PRIMITIVES_H
