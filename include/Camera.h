#ifndef OPENGL_PRJ_CAMERA_H
#define OPENGL_PRJ_CAMERA_H

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <utility>

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

        void setWH(int w, int h){ windowWidth = w; windowHeight = h;}
        std::pair<int, int> getWH() {return std::make_pair(windowWidth, windowHeight); }const;

        // Vclip = Mprojection � Mview � Mmodel � Vlocal;
        glm::mat4 getViewMatrix() const;
        glm::mat4 getProjectionMatrix() const;
        glm::vec3 getPosition() {return  position;} const;
        glm::vec3 front() const;
        glm::vec3 right() {return  glm::normalize(glm::cross(front(), up));} const;

        void setPosition(glm::vec3 pos) { position = pos;}
        void setRotation(int pitch_deg, int yaw_deg) {yaw = yaw_deg; pitch = pitch_deg;}

    public:
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
