// vertex shader
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aColor;
layout (location=2) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 ourTexCoord;

uniform mat4 model;
uniform mat4 camMatrix;

void main()
{
   gl_Position = camMatrix * model * vec4(aPos, 1.0);
   ourColor = aColor;
   ourTexCoord = aTexCoord;
}

// fragment shader
#version 330 core

in vec3 ourColor;
in vec2 ourTexCoord;
out vec4 FragColor;

uniform sampler2D tex0;

void main()
{
   FragColor = texture(tex0, ourTexCoord);
}