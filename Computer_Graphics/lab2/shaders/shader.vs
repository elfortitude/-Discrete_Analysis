#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
out vec3 ourColor;

uniform mat4 MVP;

void main()
{
    gl_Position = MVP * vec4(position, 1.0f);
    ourColor = color;
}