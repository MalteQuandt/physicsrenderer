#version 330 core

in vec3 pos;

out vec4 FragColor;

void main()
{
    FragColor = vec4(pos, 0.5f);
}