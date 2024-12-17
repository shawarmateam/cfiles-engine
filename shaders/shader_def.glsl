// vertex shader
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;
layout (location=3) in vec3 aNormal;
out vec3 ourColor;
out vec2 ourTexCoord;
out vec3 ourNormal;
out vec3 ourPosition;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
   ourPosition = vec3(model * vec4(aPos, 1.0));

   gl_Position = camMatrix * vec4(ourPosition, 1.0);
   ourColor = aColor;
   ourTexCoord = aTexCoord;
   ourNormal = aNormal;
}

// fragment shader
#version 330 core

in vec3 ourColor;
in vec2 ourTexCoord;
in vec3 ourNormal;
in vec3 ourPosition;
out vec4 FragColor;

uniform sampler2D tex0;
uniform vec4 lightColor;
uniform vec3 lightPos;

void main()
{
   float ambient = 0.2f;

   vec3 normal = normalize(ourNormal);
   vec3 lightDir = normalize(lightPos - ourPosition);

   float diff = max(dot(lightDir, normal), 0.0);

   FragColor = texture(tex0, ourTexCoord) * lightColor * (diff + ambient);
}
