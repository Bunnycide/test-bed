#version 300 es

precision mediump float;

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;

// Flags to indicate presence of maps
uniform bool hasNormalMap;
uniform bool hasSpecularMap;
uniform bool hasHeightMap;

struct Material{
    sampler2D diffuseMaps[6];
    sampler2D normalMaps[6];
    sampler2D specularMaps[6];
    sampler2D heightMaps[6];
    float shininess;
};
uniform Material material;

// Lights
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirectionalLight dirLight;

struct PointLight {
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform PointLight pointLights[4]; // Adjust the size according to your needs
uniform int numPointLights;

struct SpotLight {
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLights[4]; // Adjust the size according to your needs
uniform int numSpotLights;

uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

const float gamma = 2.2;

// Function prototypes
vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 albedo);
vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo);
vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo);
vec2 parallaxMapping(vec2 texCoords, vec3 viewDir);
vec3 gammaCorrect(vec3 color, float gamma);
vec4 blinnPhong();
vec4 usePBR();

void main()
{
    FragColor = blinnPhong();
}

vec4 usePBR(){
    
}

vec4 blinnPhong(){
    vec3 result = vec3(0.0);
    vec3 albedo;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec2 texCoords = TexCoords;

    if (hasHeightMap) {
        texCoords = parallaxMapping(TexCoords, viewDir);
    }

    albedo += texture(material.diffuseMaps[0], TexCoords).rgb;


    vec3 normal = hasNormalMap ? normalize(texture(material.normalMaps[0], TexCoords).xyz * 2.0 - 1.0) : normalize(Normal);

    result += calculateDirectionalLight(dirLight, normal, viewDir, albedo);

    for (int i = 0; i < numPointLights; ++i) {
        result += calculatePointLight(pointLights[i], normal, FragPos, viewDir, albedo);
    }

    if(numSpotLights > 0){
        for(int i =0; i < numSpotLights; i++){
            result += calculateSpotLight(spotLights[i], normal, FragPos, viewDir, albedo);
        }
    }

    return vec4(result, 1.0);
}

vec2 parallaxMapping(vec2 texCoords, vec3 viewDir) {
    float height = texture(material.heightMaps[0], texCoords).r;
    vec2 p = viewDir.xy * (height * 0.1); // scale factor for height
    return texCoords - p;
}

vec3 gammaCorrect(vec3 color, float gamma) {
    return pow(color, vec3(1.0 / gamma));
}

vec3 calculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(-light.direction);
    vec3 reflectDir = reflect(-lightDir, normal);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    float spec = 0.0;
    if (diff > 0.0) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    }

    // Combine results
    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec *  texture(material.specularMaps[0], TexCoords).rgb;
    vec3 result =  ambient + diffuse + specular;
    if (length(result)  > 0.0) return result;

    return albedo;
}

vec3 calculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    float spec = 0.0;
    if (diff > 0.0) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    }

    // Combine results
    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec * (hasSpecularMap ? texture(material.specularMaps[0], TexCoords).rgb : vec3(1.0));
    ambient *= attenuation;
    diffuse *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 calculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir, vec3 albedo) {
    vec3 lightDir = normalize(light.position - fragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);

    // Specular shading
    float spec = 0.0;
    if (diff > 0.0) {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);
    }

    // Combine results
    vec3 ambient = light.ambient * albedo;
    vec3 diffuse = light.diffuse * diff * albedo;
    vec3 specular = light.specular * spec * (hasSpecularMap ? texture(material.specularMaps[0], TexCoords).rgb : vec3(1.0));
    ambient *= attenuation * intensity;
    diffuse *= attenuation * intensity;
    specular *= attenuation * intensity;

    return (ambient + diffuse + specular);
}
