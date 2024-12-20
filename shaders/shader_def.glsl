// vertex shader
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;
layout (location=3) in vec3 aNormal;
out vec3 ourColor;
out vec2 ourTexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
   FragPos = vec3(model * vec4(aPos, 1.0));
   Normal = mat3(transpose(inverse(model))) * aNormal;
   
   gl_Position = camMatrix * vec4(FragPos, 1.0);
   ourColor = aColor;
   ourTexCoord = aTexCoord;
}

// fragment shader
#version 330 core

in vec3 ourColor;
in vec2 ourTexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

uniform sampler2D tex0;
uniform sampler2D tex1;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() {
   vec3 lightVec = lightPos - FragPos;
   float lightDist = length(lightVec);
   float a = 1.0f;
   float b = 0.04f;
   float intensity = 1.0f / (a * lightDist * lightDist + b * lightDist + 1.0f);

   float ambient = 0.2f;

   vec3 normal = normalize(Normal);
   vec3 lightDir = normalize(lightVec);

   float diff = max(dot(normal, lightDir), 0.0);

   float specularStrength = 0.5f;
   vec3 viewDir = normalize(camPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
   float specular = specularStrength * spec;

   vec4 texColor = texture(tex0, ourTexCoord);
   vec4 texColor2 = texture(tex1, ourTexCoord);
   vec4 result = (texColor * (diff * intensity + ambient) + texColor2.r * specular * intensity) * lightColor;

   return result;
}

vec4 directionalLight() {
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    
    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDirection), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec;

    vec4 texColor = texture(tex0, ourTexCoord);
    vec4 texColor2 = texture(tex1, ourTexCoord);
    
    vec4 result = (texColor * (diff + ambient) + texColor2.r * specular) * lightColor;

    return result;
}

vec4 spotLight() {
    float outerCone = 0.9f;
    float innerCone = 0.95f;

    vec3 lightDirection = normalize(lightPos - FragPos);
    
    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDirection), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec;

    float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);

    vec4 texColor = texture(tex0, ourTexCoord);
    vec4 texColor2 = texture(tex1, ourTexCoord);
    
    vec4 result = (texColor * (diff + ambient) + texColor2.r * specular) * lightColor;

    return result;
}

void main()
{


   FragColor = spotLight();
}
