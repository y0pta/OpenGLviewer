#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

glm::mat4 Camera::getViewMatrix() const{
    return glm::lookAt(position,  position + front(), up);
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(float(fov)),
                            float(windowWidth) / windowHeight ,
                            0.1f,
                            100.0f);
}

glm::vec3 Camera::front() const{
    auto Q = glm::quat(glm::vec3(glm::radians(float(pitch)),
                                 glm::radians(float(yaw)),
                                 0));
    Q = normalize(Q);
    return glm::vec3(mat4_cast(Q) * glm::vec4(0.0f, 0.0f, -1.0f, 1));
}