// vertex shader
#version 430 core

layout (location = 0) in vec3 vertices;
layout (location = 1) in vec2 textures;

out vec2 tex_coords;
uniform mat4 projection;

void main()
{
    tex_coords = textures;
    gl_Position = projection * vec4(vertices, 1.0);
}

// fragment shader
#version 430 core

out vec4 color;
uniform sampler2D sampler;

in vec2 tex_coords;

void main()
{
    color = texture(sampler, tex_coords);
}

