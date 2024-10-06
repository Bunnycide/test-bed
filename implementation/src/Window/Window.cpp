#include <Window/Window.h>

WindowStatusCodes Window::create() {
    if (!glfwInit())
    {
        return WIN_CREATE_FAILED;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

    this->window = glfwCreateWindow(this->width, this->height,
                                      this->windowName.c_str(), NULL, NULL);

    if(!this->window) return WIN_CREATE_FAILED;

    glfwMakeContextCurrent(window);

    return WIN_CREATE_SUCCESS;
}

WindowStatusCodes Window::destroy(){
    glfwTerminate();

    return WIN_DESTROYED;
}

GLFWwindow * Window::getWindowHandle() const {
    return this->window;
}
