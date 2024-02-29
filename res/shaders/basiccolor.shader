#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec4 color;   // Color attribute

out vec4 FragColor; // Varying variable to pass color to fs

void main() {
    gl_Position = vec4(position, 1.0);
    FragColor = color; // Output color
};

#shader fragment
#version 330 core

in vec4 FragColor; // Color passed from the vertex shader

layout(location = 0) out vec4 color;

void main() {
    color = FragColor;
};