#version 330 core
layout (location = 0) in vec3 aPos; // Position vector for this vertex

// Output data from this vertex shader object
out vec4 color;

// Uniform/globals of this vertex shader
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Entry point
void main()
{
    // Calculate the position of each vertex in projection space
    gl_Position = projection * view * model * vec4(aPos, 1.0);

    color=vec4(1,0,0,1);
}