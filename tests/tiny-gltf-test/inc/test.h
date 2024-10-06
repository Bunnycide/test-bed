#ifndef test_H_
#define test_H_

#include <iostream>
#include <Window/Window.h>
#include <Application/Application.h>
#include <gltfLoader/gltfLoader.h>


class MyApp : public Application {
private:
    Window window;

public:
  
    explicit MyApp(const Window &window);

    void onKeyPressed(int key,
                      int scancode,
                      int action,
                      int mods) override;
    void updateFrame(double deltaTime) override;

    void onMouseMove(double xpos, double ypos) override;
};

#endif
