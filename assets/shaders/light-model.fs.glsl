#version 300 es

precision mediump float;

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

struct Material{
    sampler2D texture_diffuse1;
    sampler2D texture_diffuse2;
    sampler2D texture_diffuse3;

    sampler2D texture_specular1;
    sampler2D texture_specular2;
    sampler2D texture_specular3;
};

uniform Material material;
uniform vec3 lightColor;

void main()
{
    FragColor = texture(material.texture_diffuse1, TexCoords);
}