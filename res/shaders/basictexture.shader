#shader vertex
#version 330 core

layout(location = 0) in vec3 vertPosition;
layout(location = 2) in vec2 texCoord;

out vec2 v_TexCoord;

void main() {
    gl_Position = vec4(vertPosition, 1.0);
    v_TexCoord = texCoord;
};

#shader fragment
#version 330 core

in vec2 v_TexCoord;

uniform vec4 u_Color;
uniform sampler2D u_Texture;


layout(location = 0) out vec4 color;

void main() {

    vec4 texColor = texture(u_Texture, v_TexCoord);
    color = texColor;
};