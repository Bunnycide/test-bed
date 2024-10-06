#include <Application/Application.h>

ApplicationState Application::loop() {
    lastTime = glfwGetTime(), timer = lastTime;

    while (!glfwWindowShouldClose(window.getWindowHandle()))
    {
        glfwPollEvents();

        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime);
        lastTime = nowTime;

        while(deltaTime >= 1.0){
            glfwSwapBuffers(window.getWindowHandle());
            updates++;
            deltaTime--;
        }

        glfwSwapBuffers(window.getWindowHandle());

        updateFrame(0.0f);
        frames++;

        if(glfwGetTime() - timer > 1.0){
            timer++;
            // Log::debug("FPS: %d Updates: %d \n", frames, updates);
            updates = 0.0, frames = 0.0;
        }
    }

    return ApplicationState::DESTROYED;
}

void Application::keyCallBackStatic(GLFWwindow *window, int key, int scancode, int action, int mods) {
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if(app){
        app->onKeyPressed(key, scancode, action, mods);
    }
}


Application::Application(Window m_window) {
    window = m_window;
    // Set up the OpenGL context, better to use GLAD for this
    glfwSwapInterval(1);
    if(! gladLoadGLES2Loader((GLADloadproc)glfwGetProcAddress)){
        Log::error("Failed to load GLES3.2");
    }

    // glfwSetInputMode(window.getWindowHandle(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(window.getWindowHandle(), this);
    glfwSetKeyCallback(window.getWindowHandle(), keyCallBackStatic);
    glfwSetCursorPosCallback(window.getWindowHandle(), mouseCallBackStatic);
}

void Application::mouseCallBackStatic(GLFWwindow *window, double xpos, double ypos) {
    auto* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    if(app){
        app->onMouseMove(xpos, ypos);
    }
}

