//
// Created by Liza on 3/16/2023.
//
#include "Shader.h"
#ifndef RESOURCE_DIR
    #define RESOURCE_DIR ""
#endif

std::string make_path(char* dir, char* fname)
{
    std::string path(dir);
    path.append("/");
    path.append(fname);
    return path;
}

Shader& Shader::instance(ShaderType type)
{
    static Shader axes(make_path(RESOURCE_DIR, "shaders/pos_color.vs"), make_path(RESOURCE_DIR, "shaders/pos_color.fs"));
    static Shader boxDemo(make_path(RESOURCE_DIR, "shaders/box_demo.vs"), make_path(RESOURCE_DIR, "shaders/box_demo.fs"));
    static Shader mesh(make_path( RESOURCE_DIR,  "shaders/mesh.vs") , make_path( RESOURCE_DIR, "shaders/mesh.fs"));
    switch (type) {
        case eAxes:
            return axes;
        case eBoxDemo:
            return boxDemo;
        case eMesh:
            return mesh;
        default:
            axes;
    }
}

Shader::Shader(const std::string& vertexPath, const std::string &fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;

    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;

        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        vShaderFile.close();
        fShaderFile.close();

        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch (std::ifstream::failure& e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    const char* vShaderCode = vertexCode.c_str();
    const char* fShaderCode = fragmentCode.c_str();

    unsigned int vertex, fragment;

    // Create and compile vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    // Create and compile fragment  shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    // Attach shaders
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    // free resources
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
    std::cout<< "shader " << ID << " deleted." << std::endl;
    glDeleteProgram(ID);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
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