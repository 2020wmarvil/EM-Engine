#version 330 core

in vec2 v_TexCoord;

uniform vec2 u_TexOffset;
uniform sampler2D u_Texture;

out vec4 color;

void main() {
    color = texture(u_Texture, v_TexCoord+u_TexOffset);
}
