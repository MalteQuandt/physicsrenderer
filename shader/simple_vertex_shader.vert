#version 330 core
layout (location = 0) in vec3 aPos;

out vec3 pos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // Calculate the position of each vertex in projection space
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    pos=aPos+1.0f;
}