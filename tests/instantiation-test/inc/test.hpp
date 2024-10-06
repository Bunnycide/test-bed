#include <Application/Application.h>
#include <Shader/ShaderProgram.h>


class MyApp : public Application
{
public:
    explicit MyApp(const Window &window);

    void onMouseMove(double xpos, double ypos) override;
    void updateFrame(double deltaTime) override;
    void onKeyPressed(int key,
                      int scancode,
                      int action,
                      int mods) override;
private:
    GLuint *vbo, *ebo, *aabo;
    ShaderProgram shader_program;
};
