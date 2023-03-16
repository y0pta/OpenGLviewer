//
// Created by Liza on 3/13/2023.
//

#ifndef OPENGL_PRJ_GLFW_HELPFUNC_CPP
#define OPENGL_PRJ_GLFW_HELPFUNC_CPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


/*bool screenshot(int w, int h, const std::string &savePath)
{
    int channels = 3;
    GLenum format = GL_RGB;

    unsigned char *pixels = new unsigned char[ channels * w * h ];
    glReadPixels( 0, 0, w, h, format, GL_UNSIGNED_BYTE, pixels);
    if (glGetError() != GL_NO_ERROR){
        delete[] pixels;
        return false;
    }
    // flip pixels (gl has inversed vertical-axe)
    stbi_set_flip_vertically_on_load(1);

    // write bmp with stb
    int res = stbi_write_bmp(savePath.c_str(), w, h, channels, pixels);
    std::cout << "Snapshot captured. File: " << savePath <<". Code:" << res << std::endl;

    // return flip flag
    stbi_flip_vertically_on_write(0);
    delete[] pixels;
    return true;
}*/

void resizeCallback(GLFWwindow* window, int width, int height)
{
    // check window size applied
    glViewport(0, 0, width, height);
}

void *createWindow(int w, int h, bool setCallbacks = true){
    // glfw: init and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true); // remove for release
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // try GLFW_OPENGL_CORE_PROFILE  GLFW_OPENGL_COMPAT_PROFILE

    // glfw: create window
    GLFWwindow* window = glfwCreateWindow(w, h, "Test window", NULL, NULL);
    if (window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW. " << glewGetErrorString(err)<< std::endl;
        return nullptr;
    }
    else
    {
        std::cout<< "Glew version:"<<glewGetString(GLEW_VERSION) <<std::endl;
    }

    glfwSetWindowSizeCallback(window, resizeCallback);

    return window;
}

#endif //OPENGL_PRJ_GLFW_HELPFUNC_CPP
