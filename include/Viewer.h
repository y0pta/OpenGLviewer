#ifndef OPENGL_PRJ_VIEWER_H
#define OPENGL_PRJ_VIEWER_H

#include <iostream>
#include <functional>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "Shader.h"
#include <memory>

class Viewer{
    public:
        Viewer(int w = 1200, int h = 1080);
        ~Viewer();

        //void processKeys();
        void terminate();
        void show();
        void showTestBox();
        void showTestMesh();
        void showDepthTest();

        //Callbacks
        std::function<void(Viewer& viewer, double x, double y)> callback_mouse_move;
        std::function<void(Viewer& viewer, double yOffset)> callback_mouse_scroll;
        std::function<bool(Viewer& viewer, int button, int modifier)> callback_mouse_down;
        std::function<bool(Viewer& viewer, int button, int modifier)> callback_mouse_up;
        std::function<void(Viewer& viewer, unsigned int key, int modifiers, int action)> callback_key_action;
        std::function<bool(Viewer& viewer, int w, int h)> callback_post_resize;
        std::function<void(Viewer& viewer)> callback_display;
        std::function<void(Viewer& viewer)> callback_close;

    protected:
        void _loadResources();
        void _freeResources();

    public:
        GLFWwindow* window;
        // actual W, H, update with activeScene
        int w;
        int h;

        // State flags
        bool CLOSE_FLAG = false;

        // Keyboard & mouse data
        double lastMouseX;
        double lastMouseY;
        double mouseWheelOffset = 0;

        // Time and movement speed
        std::unique_ptr<Camera> camera;
        float camera_speed = 0.01f;
};


#endif //OPENGL_PRJ_VIEWER_H
