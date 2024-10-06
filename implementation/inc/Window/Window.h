/**

Author : Jae Bhadane - Huawei 2024
Email  : jae.bhadane@huawei.com

A class meant to manage window, context and window i/p using GLFW api
*/

#ifndef OGL_MODEL_LOADER_WINDOW_H
#define OGL_MODEL_LOADER_WINDOW_H

#define GLFW_INCLUDE_NONE
#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_EGL

#include <string>
#include "GLFW/glfw3.h"

enum WindowStatusCodes{
    WIN_CREATE_FAILED,
    WIN_CREATE_SUCCESS,
    WIN_DESTROYED
};

class Window{
public:
    //Default Constructors
  Window() : 
    windowName("default window"), width(800), height(600) {};

  Window(   std::string m_windowName, 
            uint16_t    m_width,
            uint16_t    m_height) : 
    windowName("default window"), width(m_width), height(m_height) {};

  uint16_t width; // Window width
  uint16_t height; // Window height

  //Create a window
  WindowStatusCodes create();
  WindowStatusCodes destroy();

  GLFWwindow * getWindowHandle() const;

private:
    // The window title
    std::string windowName;

    // GLFW window pointer
    GLFWwindow* window;
};

#endif // OGL_MODEL_LOADER_WINDOW_H
