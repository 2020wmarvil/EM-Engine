// shader fragment

#version 330 core

out vec4 color;

uniform vec3 u_LampColor;

void main() {
    color = vec4(u_LampColor, 1.0f);
}
