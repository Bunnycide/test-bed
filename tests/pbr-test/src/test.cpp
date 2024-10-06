#include "../inc/test.h"

#include <GeneralUtils/fileutils.h>

using namespace std;

MyApp::MyApp(const Window& window) : Application(window) {
    this->window = window;
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    // Load the gltf file
    const std::string assetPath = getAssetPath(
                "Env_with_Character_and_Lights.gltf", "models/demoscene/Gltf_v04_Lights"
                );
    asset model = loadGltf(assetPath);
}

void MyApp::onKeyPressed(int key,
                         int scancode,
                         int action,
                         int mods)  {

}

void MyApp::updateFrame(double deltaTime)  {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MyApp::onMouseMove(double xpos, double ypos){

}

int main(){
    Window window;
    auto retCode = window.create();

    MyApp myApp(window);
    auto appState = myApp.loop();
}
