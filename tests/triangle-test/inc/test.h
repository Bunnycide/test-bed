#ifndef test_H_
#define test_H_

#include <iostream>
#include <Window/Window.h>
#include <Application/Application.h>
#include "Shader/ShaderProgram.h"
#include "Texture/Texture2D.h"
#include "Model/Mesh.h"
#include "Camera/Camera.h"
#include "Model/Model.h"

struct cameraData_t{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
};

class MyApp : public Application {
private:
    Window window;
    Texture2D texture2D;
    Camera camera;
    cameraData_t cameraData{};
    Model demoScene;

    float mouseXPos, mouseYPos, mouseXOffset, mouseYOffset, mouseLastX, mouseLastY;
    bool firstMouse = true;

    std::vector<ShaderProgram*> shaders;

public:
  
    explicit MyApp(const Window &window);

    ShaderProgram modelShaderProgram, lightShaderProgram;

    void onKeyPressed(int key,
                      int scancode,
                      int action,
                      int mods) override;

    void onMouseMove(double xpos, double ypos) override;
    void updateFrame(double deltaTime) override;
    void compileAllShaders();
    void setupCamera();
    void loadModels();
    void updateViewAndProjectionMatrices();
};

#endif
