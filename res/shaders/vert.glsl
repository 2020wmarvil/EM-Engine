#version 330 core

layout(location = 0) in vec4 position;

uniform vec3 u_Move;

void main() {
	gl_Position = position + vec4(u_Move, 0.0f);
}