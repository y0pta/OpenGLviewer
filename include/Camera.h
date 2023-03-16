//
// Created by Liza on 3/13/2023.
//

#ifndef OPENGL_PRJ_CAMERA_H
#define OPENGL_PRJ_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        Camera(int WindowWidth, int WindowHeight,
               const glm::vec3 &position = glm::vec3(2.0f, 1.0f, 3.0f),
               const glm::vec3 &up = glm::vec3(0.0f, 1.0f, 0.0f),
               int pitch_deg = 0,
               int yaw_deg = 0)
               :    windowWidth(WindowWidth),
                    windowHeight(WindowHeight),
                    position(position),
                    up(up),
                    pitch(pitch_deg),
                    yaw(yaw_deg){}
        ~Camera(){}

        void ProcessMouseMove(double x, double y);
        void ProcessKeyboard(int key);
        void ProcessWheel(double offset, double screenX, double screenY);
        void setWidthHeight(int w, int h){ windowWidth = w; windowHeight = h;}

        // Vclip = Mprojection × Mview × Mmodel × Vlocal;
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
        glm::vec3 front() const;

        void setPosition(glm::vec3 pos) { position = pos;}
        void setRotation(int pitch_deg, int yaw_deg) {yaw = yaw_deg; pitch = pitch_deg;}

    public:
        float speed = 0.01f;

        int fov = 60;
        double zoom = 1.f;

    protected:
        glm::vec3 position;
        glm::vec3 up;

        int pitch; // x-axis  rotation (freeze -90 90)
        int yaw; // y- axis  rotation (full circle)

        int windowWidth;
        int windowHeight;
};


#endif //OPENGL_PRJ_CAMERA_H
