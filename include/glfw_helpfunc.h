//
// Created by Liza on 3/13/2023.
//

#ifndef OPENGL_PRJ_GLFW_HELPFUNC_CPP
#define OPENGL_PRJ_GLFW_HELPFUNC_CPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

void resizeCallback(GLFWwindow* window, int width, int height);
void *createWindow(int w, int h, bool setCallbacks = true);
void gl_check_error(const char* function, const char *file, int line);

#endif //OPENGL_PRJ_GLFW_HELPFUNC_CPP
