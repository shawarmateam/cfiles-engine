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
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

void main()
{
   float ambient = 0.2f;

   vec3 normal = normalize(Normal);
   vec3 lightDir = normalize(lightPos - FragPos);

   float diff = max(dot(normal, lightDir), 0.0);

   float specularStrength = 0.5f;
   vec3 viewDir = normalize(camPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
   float specular = specularStrength * spec;

   vec4 texColor = texture(tex0, ourTexCoord);
   vec4 result = texColor * lightColor * (ambient + diff + specular);
   FragColor = result;
}
