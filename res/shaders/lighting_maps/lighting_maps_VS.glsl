// vertex shader

#version 330 core
  
layout(location = 0) in vec4 a_Pos;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec3 a_Color;
layout(location = 3) in vec2 a_TexCoord;

out vec3 v_Normal;
out vec3 v_Color;
out vec2 v_TexCoord;
out vec3 v_FragPos;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;
uniform mat4 u_ModelView;
uniform mat4 u_ViewProj;
uniform mat4 u_MVP;

void main() {
	v_Normal = mat3(transpose(inverse(u_ModelView))) * a_Normal;
	v_Color = a_Color;
	v_TexCoord = a_TexCoord;
	v_FragPos = vec3(u_ModelView * a_Pos);

	gl_Position = u_MVP * a_Pos;
};