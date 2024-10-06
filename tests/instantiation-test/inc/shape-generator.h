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


void generate_hexagon(  std::vector<GLfloat>& vertice,
                        GLfloat h_r,
                        std::pair<GLfloat, GLfloat> centre)
{
#define SIDES_OF_HEXGON 6

    auto x = 0.0f, y = 0.0f;

    for(auto i = 0 ; i < SIDES_OF_HEXGON; i++)
    {
        x = h_r * std::cos( std::cos((M_PI * 6 ) / i ));

    }
}