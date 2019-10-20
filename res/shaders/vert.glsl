#version 330 core

layout(location = 0) in vec4 position;

uniform vec3 u_Transform;

void main() {
	gl_Position = vec4(u_Transform, 0.0f) + position;
}