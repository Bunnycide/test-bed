#include <glm/glm.hpp>
#include <math.h>

using namespace std;

std::vector<GLfloat> square_vertices = {
    0.5f, .5f, 0.0f,
    0.5f, -.5f, 0.0f,
    -0.5f, -.5f, 0.0f,
    -0.5f, .5f, 0.0f,
};

std::vector<GLuint> square_indices = {
    0, 1, 2,
    0, 2, 3
};


inline void generate_hexagon(   std::vector<GLfloat>& vertices,
                                GLfloat h_r,
                                std::pair<GLfloat, GLfloat> centre)
{
#define SIDES_OF_HEXGON 6

    GLfloat x = 0.0f, y = 0.0f;

    vertices.resize(6 * 9);

    for(auto i = 0 ; i < SIDES_OF_HEXGON / 2; i++)
    {
        x = std::cos(M_PI / 3 * static_cast<double>(i)) * h_r;
        y = std::sin(M_PI / 3 * static_cast<double>(i)) * h_r;

        vertices.insert(vertices.begin(), {x, y, 0.0f});
    }
}