#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 tex_coords;

uniform mat4 u_MVP;

out vec2 v_TexCoord;

void main() {
	v_TexCoord = tex_coords;
	gl_Position = u_MVP * position;
}