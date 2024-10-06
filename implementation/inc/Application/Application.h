#ifndef OGL_MODEL_LOADER_APPLICATION_H
#define OGL_MODEL_LOADER_APPLICATION_H

#include <Log/Log.h>

#include "Window/Window.h"
#include <glad/glad.h>

enum ApplicationState{
    STARTED,
    SUSPENDED,
    DESTROYED
};

class Application {
public:
    explicit Application (Window m_window);
    ApplicationState loop();

    double deltaTime = 0.0f;

private:
    Window window;

    virtual void onKeyPressed(int, int, int, int) = 0;
    virtual void onMouseMove(double xpos, double ypos) = 0;
    virtual void updateFrame(double deltaTime) = 0;


    // Frame rate calculation vars
    double lastTime = 0.0f, timer = 0.0;
    double nowTime = 0.0f;
    double limitFPS = 1.0 / 60.0;
    int frames = 0, updates = 0;

    static void keyCallBackStatic(  GLFWwindow *window,
                                    int key,
                                    int scancode,
                                    int action,
                                    int mods);

    static void mouseCallBackStatic(GLFWwindow* window, double xpos, double ypos);
};

#endif //OGL_MODEL_LOADER_APPLICATION_H
