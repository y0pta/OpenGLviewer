//
// Created by Liza on 3/13/2023.
//
#include "Viewer.h"
#include "glfw_helpfunc.h"
#include <glm/gtx/string_cast.hpp>
#include "Primitives.h"
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#include "Mesh.h"
#ifndef RESOURCE_DIR
    #define RESOURCE_DIR ""
#endif

static Viewer* __viewer = nullptr;

void mouseScrollCallback(GLFWwindow* window,double xOffset,double yOffset)
{
    __viewer->callback_mouse_scroll(*(__viewer), yOffset);
}

void mouseMoveCallback(GLFWwindow* window,double x,double y)
{
    __viewer->callback_mouse_move(*(__viewer), x, y);
    __viewer->lastMouseX = x;
    __viewer->lastMouseY = y;
}

void closeCallback(GLFWwindow* window)
{
    if (__viewer)
        __viewer->callback_close(*(__viewer));
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    // Better use force processing, ie ask input every frame
    if (__viewer && (action == GLFW_PRESS))
        __viewer->callback_key_action(*(__viewer), key, mods, action);
}

void processMouseMove(Viewer& viewer, double x, double y)
{
    int lbStatus = glfwGetMouseButton(viewer.window, GLFW_MOUSE_BUTTON_LEFT);
    int rbStatus = glfwGetMouseButton(viewer.window, GLFW_MOUSE_BUTTON_RIGHT);

    double xOffset = x - viewer.lastMouseX;
    double yOffset = viewer.lastMouseY - y; // inverted due to y axe directed from top to bottom

    // apply to camera movement
    auto wh = viewer.camera->getWH();

    double screenX = x / wh.first;
    double screenY = y / wh.second;
    screenX -= 0.5;
    screenY -= 0.5;

    double pitch = - 90 * screenY;
    pitch = glm::clamp(pitch, -89.0, 89.0);

    double yaw = - 90 * screenX;
    while (yaw < -179)
        yaw += 360;
    while (yaw > 179)
        yaw -= 360;

    viewer.camera->setRotation(pitch, yaw);
}

void processScroll(Viewer& viewer, double yOffset)
{
    /// yOffset > 0 if ZoomIn (wheel moves forward)
    /// yOffset < 0 if ZoomOt (wheel moves backward)
    ///  min = -1, max = +1

    //std::cout << "wheel value" << yOffset/5.0 << std::endl;
    double zoom = viewer.camera->getZoom() + yOffset / 10.0;

    viewer.camera->setZoom( zoom);
}

void defaultClose(Viewer& viewer)
{
    std::cout << "Close callback received" << std::endl;
    viewer.CLOSE_FLAG = true;
    glfwTerminate();
}

void processKey(Viewer& viewer, unsigned int key, int modifiers, int action){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        defaultClose(viewer);
    }
    else if (action == GLFW_PRESS) {
        auto& camera = viewer.camera;
        float speed = viewer.camera_speed;
        switch (key) {
            case GLFW_KEY_UP:
                camera->setPosition(camera->getPosition() + camera->front() * speed);
                break;
            case GLFW_KEY_DOWN:
                camera->setPosition(camera->getPosition() - camera->front() * speed);
                break;
            case GLFW_KEY_RIGHT:
                camera->setPosition(camera->getPosition() + camera->right() * speed);
                break;
            case GLFW_KEY_LEFT:
                camera->setPosition(camera->getPosition() - camera->right() * speed);
                break;
            default:
                break;
        }
    }
}

void getProcessKeys(Viewer& viewer){
    if (glfwGetKey(viewer.window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        defaultClose(viewer);
    }
    auto& camera = viewer.camera;
    float speed = viewer.camera_speed;

    if (glfwGetKey(viewer.window, GLFW_KEY_UP) == GLFW_PRESS)
        camera->setPosition(camera->getPosition() + camera->front() * speed);
    else if (glfwGetKey(viewer.window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera->setPosition(camera->getPosition() - camera->front() * speed);
    else if (glfwGetKey(viewer.window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera->setPosition(camera->getPosition() + camera->right() * speed);
    else if (glfwGetKey(viewer.window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera->setPosition(camera->getPosition() - camera->right() * speed);
    else if (glfwGetKey(viewer.window, GLFW_KEY_R) == GLFW_PRESS) {
        camera->setZoom(1);
        camera->setPosition( glm::vec3(2.0f, 1.0f, 3.0f));
        camera->setRotation(0,0);
    }
}

Viewer::Viewer(int w, int h) : w(w), h(h)
{
    std::cout << "=== Control keys ==="<< std::endl;
    std::cout << "ESC - close."<< std::endl;
    std::cout << "R - reset camera to origin."<< std::endl;

    __viewer = this;
    lastMouseX = w/2.0;
    lastMouseY = h/2.0;
    window = reinterpret_cast<GLFWwindow*>(createWindow(w,h));

    callback_mouse_move = processMouseMove;
    callback_mouse_scroll = processScroll;
    callback_close = defaultClose;

    // callbacks
    glfwSetCursorPosCallback(window, mouseMoveCallback);
    glfwSetScrollCallback(window, mouseScrollCallback);
    glfwSetWindowCloseCallback(window, closeCallback);

    // set cursor mode
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Viewer::~Viewer()
{
    glfwTerminate();
}

void Viewer::showTestBox() {
    // world cube positions
    glm::vec3 cubePositions[] = {
            glm::vec3(0.0f,  0.0f,  0.0f),
            glm::vec3(2.0f,  5.0f, -15.0f),
            glm::vec3(-1.5f, -2.2f, -2.5f),
            glm::vec3(-3.8f, -2.0f, -12.3f),
            glm::vec3(2.4f, -0.4f, -3.5f),
            glm::vec3(-1.7f,  3.0f, -7.5f),
            glm::vec3(1.3f, -2.0f, -2.5f),
            glm::vec3(1.5f,  2.0f, -2.5f),
            glm::vec3(1.5f,  0.2f, -1.5f),
            glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    //set up projection matrix
    camera = std::make_unique<Camera>(w, h);
    Axes axes;
    Axes axes1;
    axes1.setOrigin(glm::vec3(1,2,3));
    axes1.setScale(0.5);

    TexturedCube boxes[10];
    for (unsigned int i = 0; i < 10; i++)
    {
        boxes[i].setOrigin(cubePositions[i]);
        boxes[i].setRotation(glm::vec3(
                                glm::radians(20.f * i),
                                glm::radians(20.f * i),
                                glm::radians(20.f * i)));
    }

    while (!CLOSE_FLAG) {
        getProcessKeys(*this);
        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        axes.render(camera.get());
        axes1.render(camera.get());

        for (unsigned int i = 0; i < 10; i++)
        {
            boxes[i].render(camera.get());
        }

        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Viewer::showTestMesh() {
    //set up projection matrix
    camera = std::make_unique<Camera>(w, h);
    Axes axes;
    Mesh m(make_path(RESOURCE_DIR, "samples/meshes/backpack/backpack.obj"));

    while (!CLOSE_FLAG) {
        getProcessKeys(*this);
        // render
        glClearColor(0.4f, 0.6f, 1, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        axes.render(camera.get());
        m.render(camera.get());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Viewer::showDepthTest() {
    camera = std::make_unique<Camera>(w, h);
    Axes axes;
    Mesh m(strcat(RESOURCE_DIR, "samples/meshes/backpack/backpack.obj"));

    // Depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


}

void Viewer::show()
{
    /*
    while (!glfwWindowShouldClose(window)) {
        processKeys(scene);

        updateTime();

        glClearColor(scene->backgroundColor.r, scene->backgroundColor.g, scene->backgroundColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);

        scene->drawAll();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    // glfw: terminate, free GLFW-resources
    glfwTerminate();
    activeScene = nullptr;
     */
}

void Viewer::terminate()
{
    glfwTerminate();
}


