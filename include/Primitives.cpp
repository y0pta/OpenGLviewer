//
// Created by Liza on 3/16/2023.
//

#include "Primitives.h"
#include "Texture.h"

bool Axes::initialized = false;
unsigned int Axes::VBO = 0;
unsigned int Axes::VAO = 0;

Axes::Axes() : shader(Shader::instance(Shader::eAxes))
{
    // make initialization of VAO and VBO for all class-e
    if (!initialized) {
        Axes::_init();
        initialized = true;
    }
}

void Axes::_init(){
    float vertices[] = {
            // coords, color
            // x
            10.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
            -10.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
            // y
            0.0f, 10.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            0.0f, -10.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            // z
            0.0f, 0.0f,  10.0f,  0.4f, 0.4f, 1.0f,
            0.0f, 0.0f,  -10.0f,  0.4f, 0.4f, 1.0f,
            // arrow x
            9.0f, 0.2f,  0.0f,  1.0f, 0.0f, 0.0f,
            10.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
            10.0f, 0.0f,  0.0f,  1.0f, 0.0f, 0.0f,
            9.0f, -0.2f,  0.0f,  1.0f, 0.0f, 0.0f,
            // arrow y
            -0.2f, 9.0f,  0.0f, 0.0f, 1.0f, 0.0f,
            0.0f,10.0f,  0.0f,   0.0f, 1.0f, 0.0f,
            0.0f,10.0f,  0.0f,   0.0f, 1.0f, 0.0f,
            0.2f, 9.0f,  0.0f,  0.0f, 1.0f, 0.0f,
            // arrow z
            0.0f,  0.2f,   9.0f,  0.4f, 0.4f, 1.0f,
            0.0f,  0.0f,  10.0f,  0.4f, 0.4f, 1.0f,
            0.0f,  0.0f,  10.0f,  0.4f, 0.4f, 1.0f,
            0.0f, -0.2f, 9.0f,  0.4f, 0.4f, 1.0f,
    };
    glGenVertexArrays(1, &Axes::VAO);
    glGenBuffers(1, &Axes::VBO);

    glBindVertexArray(Axes::VAO);

    glBindBuffer(GL_ARRAY_BUFFER, Axes::VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // coord attribs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexArrayAttrib(Axes::VAO, 0);

    // color attribs
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexArrayAttrib(Axes::VAO, 1);


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Axes::render(Camera* cam) const
{
    glBindVertexArray(VAO);

    shader.use();
    auto model = glm::translate(glm::mat4(1.0f), origin)
                 * glm::scale(glm::mat4(1.0f), glm::vec3(scale));

    shader.setMat4("model", model);
    shader.setMat4("view", cam->getViewMatrix());
    shader.setMat4("projection", cam->getProjectionMatrix());

    glDrawArrays(GL_LINES, 0, 18);
    glBindVertexArray(0);
}

bool TexturedCube::initialized = false;
unsigned int TexturedCube::VBO = 0;
unsigned int TexturedCube::VAO = 0;

TexturedCube::TexturedCube() :  texture1(Texture::instance(Texture::eSmile)),
                                texture2(Texture::instance(Texture::eWoodenBox)),
                                         shader(Shader::instance(Shader::eBoxDemo))
{
    // make initialization of VAO and VBO for all class-e
    if (!initialized) {
        TexturedCube::_init();
        initialized = true;
    }
}

void TexturedCube::_init() {
    float vertices[] = {
            // coords      // texture coords
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &TexturedCube::VAO);
    glGenBuffers(1, &TexturedCube::VBO);

    glBindVertexArray(TexturedCube::VAO);

    glBindBuffer(GL_ARRAY_BUFFER, TexturedCube::VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // coord attribs
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexArrayAttrib(TexturedCube::VAO, 0);

    // texture coord attribs
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexArrayAttrib(TexturedCube::VAO, 1);
}

void TexturedCube::render(Camera* cam) const
{
    shader.use();
    shader.setTexture("texture1", 0, texture1, GL_TEXTURE0);
    shader.setTexture("texture2", 0, texture2, GL_TEXTURE0);

    shader.use();

    auto model = glm::translate(glm::mat4(1.0f), origin)
                 * glm::scale(glm::mat4(1.0f), glm::vec3(scale));
    shader.setMat4("model", model);
    shader.setMat4("projection", cam->getProjectionMatrix());

    auto view = cam->getViewMatrix();
    shader.setMat4("view", view);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}