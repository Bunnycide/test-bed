#include "../inc/test.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/gtc/type_ptr.hpp"

using namespace std;

MyApp::MyApp(const Window& window) : Application(window) {
    // Set GL state
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);

    this->window = window;
    // Setup camera
    setupCamera();
    compileAllShaders();

    loadModels();

    updateViewAndProjectionMatrices();

    modelShaderProgram.use();
    modelShaderProgram.set("lightColor", glm::vec3(0.5f, 0.9f, 0.8f));
    modelShaderProgram.set("lightPos", glm::vec3 (50.0f, 10.0f, 0.0f));
    modelShaderProgram.set("viewPos", camera.Position);
}

void MyApp::onKeyPressed(int key,
                         int scancode,
                         int action,
                         int mods)  {
    if(key == GLFW_KEY_W){
        camera.ProcessKeyboard(Camera_Movement::FORWARD, (float)deltaTime);
    }

    else if(key == GLFW_KEY_S){
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, (float)deltaTime);
    }

    else if(key == GLFW_KEY_A){
        camera.ProcessKeyboard(Camera_Movement::LEFT, (float)deltaTime);
    }

    else if(key == GLFW_KEY_D){
        camera.ProcessKeyboard(Camera_Movement::RIGHT, (float)deltaTime);
    }

    cameraData.view = camera.GetViewMatrix();
    // updateViewAndProjectionMatrices();
}

void MyApp::updateFrame(double deltaTime)  {
    glViewport(0, 0, this->window.width, this->window.height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // avocado.Draw(modelShaderProgram);
    // lightMarker.Draw(lightShaderProgram);
    demoScene.Draw(modelShaderProgram);

    glBindVertexArray(0);
}

void MyApp::onMouseMove(double xpos, double ypos) {
    mouseXPos = static_cast<float>(xpos);
    mouseYPos = static_cast<float>(ypos);

    if(firstMouse){
        mouseLastX = mouseXPos;
        mouseLastY = mouseYPos;
        firstMouse = false;
    }

    mouseXOffset = mouseXPos - mouseLastX;
    mouseYOffset = mouseYPos - mouseLastY;

    mouseLastX = mouseXPos;
    mouseLastY = mouseYPos;

    camera.ProcessMouseMovement(mouseXOffset, mouseYOffset);
    cameraData.view = camera.GetViewMatrix();
    // modelShaderProgram.set("view", camera.GetViewMatrix());
    // updateViewAndProjectionMatrices();
}

void MyApp::compileAllShaders() {
    // Compile and link shader
    modelShaderProgram.addShader("model.vs.glsl", GL_VERTEX_SHADER);
    modelShaderProgram.addShader("model.fs.glsl", GL_FRAGMENT_SHADER);

    modelShaderProgram.compile();

    lightShaderProgram.addShader("light-model.vs.glsl", GL_VERTEX_SHADER);
    lightShaderProgram.addShader("light-model.fs.glsl", GL_FRAGMENT_SHADER);

    lightShaderProgram.compile();

    shaders.push_back(&modelShaderProgram);
    shaders.push_back(&lightShaderProgram);
}

void MyApp::setupCamera() {
    auto projection = glm::perspective(glm::radians(45.0f), (float)window.width / (float)window.height, 0.1f, 1000.0f);

    camera = Camera(glm::vec3(0.0f, 1.0f, 8.0f));
    camera.MovementSpeed = 1.0f;
    cameraData.view = camera.GetViewMatrix();
    cameraData.projection = projection;
}

void MyApp::loadModels() {
    std::filesystem::path demoScenePath(R"(/home/jaeb/Workspace/ogl-model-loader/assets/models/demoscene/Gltf_v04_Lights/Env_with_Character_and_Lights.gltf)");

    demoScene = Model(demoScenePath.string().c_str());
    demoScene.rotate(190.0, glm::vec3(0.0f, 1.0f, 0.0f));
    demoScene.rotate(340.0, glm::vec3(1.0f, 0.0f, 0.0f));
}

void MyApp::updateViewAndProjectionMatrices() {

    for(auto shader : shaders){
        shader->use();
        shader->set("view", cameraData.view);
        shader->set("projection", cameraData.projection);
    }

    modelShaderProgram.set("viewPos", camera.Position);
}

int main(){
    Window window("test", 1280, 768);
    auto retCode = window.create();

    MyApp myApp(window);
    auto appState = myApp.loop();
}
