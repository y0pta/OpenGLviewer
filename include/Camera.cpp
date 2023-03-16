//
// Created by Liza on 3/13/2023.
//

#include "Camera.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

void Camera::ProcessMouseMove(double x, double y)
{
    x /= windowWidth;
    y /= windowHeight;
    x -= 0.5;
    y -= 0.5;

    pitch = - 90 * y;
    pitch = glm::clamp(pitch, -89, 89);

    yaw = - 90 * x;
    while (yaw < -179)
        yaw += 360;
    while (yaw > 179)
        yaw -= 360;

    std::cout << pitch << " " << yaw  << " " << std::endl;
    std::cout << glm::to_string(position) << std::endl;

}

void Camera::ProcessKeyboard(int key)
{
    switch (key) {
        case GLFW_KEY_UP:
            position = position + front() * speed;
            break;
        case GLFW_KEY_DOWN:
            position = position - front() * speed;
            break;
        case GLFW_KEY_RIGHT:
            position = position + glm::normalize(glm::cross(front(), up)) * speed;
            break;
        case GLFW_KEY_LEFT:
            position = position - glm::normalize(glm::cross(front(), up)) * speed;
            break;
        default:
            break;
    }
}

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