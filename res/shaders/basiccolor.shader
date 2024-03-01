#shader vertex
#version 330 core

layout(location = 0) in vec3 vertPosition;
layout(location = 1) in vec4 vertColor;   // Color attribute

out vec4 fragColor; // Varying variable to pass color to fs

void main() {
    gl_Position = vec4(vertPosition, 1.0);
    fragColor = vertColor; // Output color
};

#shader fragment
#version 330 core

in vec4 fragColor; // Color passed from the vertex shader

layout(location = 0) out vec4 color;

void main() {
    color = fragColor;
};