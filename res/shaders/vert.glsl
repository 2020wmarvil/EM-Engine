#version 330 core

layout(location = 0) in vec4 position;

//uniform vec3 u_Transform;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;
void main() {
	gl_Position = u_Model*u_View*u_Projection*position;
}
