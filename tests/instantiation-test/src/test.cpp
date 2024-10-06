#include <iostream>
#include "test.hpp"
#include "shape-generator.h"

static void fill_geometry_data( GLuint* &vbo,
                                GLuint* &ebo,
                                GLsizei vertex_buffer_size,
                                void* vertex_data,
                                GLsizei index_buffer_size,
                                void* index_data)
{
    GLuint* buffers = new GLuint[2];
    glGenBuffers(2, buffers);
    vbo = &buffers[0];
    ebo = &buffers[1];

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);

    glBufferData(GL_ARRAY_BUFFER, vertex_buffer_size, vertex_data, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size, index_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

static void setup_attribute_array(  GLuint* &aabo,
                                    const GLuint vbo,
                                    const GLuint ebo)
{
    aabo = new GLuint;

    glGenVertexArrays(1, aabo);

    glBindVertexArray(*aabo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
}

MyApp::MyApp(const Window& window) : Application(window)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);



    // Generate the vertices first
    // A square to beging with
    fill_geometry_data(vbo, ebo,
                        static_cast<GLsizei>(square_vertices.size() * sizeof(GLfloat)),
                        square_vertices.data(),
                        static_cast<GLsizei>(square_indices.size() * sizeof(GLuint)),
                        square_indices.data());

    setup_attribute_array(aabo, *vbo, *ebo);

    shader_program.addShader("instance-renderer/default.vs.glsl", GL_VERTEX_SHADER);
    shader_program.addShader("instance-renderer/default.fs.glsl", GL_FRAGMENT_SHADER);

    shader_program.compile();
    shader_program.use();
}

void MyApp::onKeyPressed(int key, int scancode, int action, int mods)
{

}

void MyApp::onMouseMove(double xpos, double ypos)
{

}

void MyApp::updateFrame(double deltaTime)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader_program.use();
    glBindVertexArray(*aabo);
    glDrawElements( GL_TRIANGLES, 6,  GL_UNSIGNED_INT, 0);
}


int main(){
    Window window("test", 1280, 768);
    auto retCode = window.create();

    MyApp myApp(window);
    auto appState = myApp.loop();
}