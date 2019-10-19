// fragment shader

#version 330 core

#define NUM_POINT_LIGHTS 4

// inputs
in vec3 v_Normal;
in vec3 v_Color;
in vec2 v_TexCoord;
in vec3 v_FragPos;

// outputs
layout(location = 0) out vec4 FragColor;

// structs
struct Material {
	sampler2D diffuse, specular, emission;
    float shininess;
}; uniform Material u_Material;

struct DirLight {
	vec3 direction;
	vec3 ambient, diffuse, specular;
}; uniform DirLight u_DirLight;

// uniforms
uniform vec3 u_CameraPos;
uniform mat4 u_View;
uniform float u_Time;
uniform sampler2D u_Texture;

// function declarations
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 cameraDir);
vec3 CalcPointLight() { return vec3(0.0f); }
vec3 CalcSpotLight()  { return vec3(0.0f); }

// main method
void main() {
	// properties
	vec3 normal = normalize(v_Normal);
	vec3 cameraDir = normalize(u_CameraPos - v_FragPos);

	vec3 resultantColor = vec3(0.0f);
	// phase 1: calculate the directional light
	resultantColor += CalcDirLight(u_DirLight, normal, cameraDir);
//	// phase 2: calculate point lights
//	for (int i=0; i<NUM_POINT_LIGHTS; i++) {
//		resultantColor += CalcPointLight();
//	}
//	// phase 3: calculate the spotlight
//	resultantColor += CalcSpotLight();

	// output the final color
	FragColor = vec4(resultantColor, 1.0f);
}

// function definitions
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 cameraDir) {
	vec3 lightDir = normalize(-light.direction);
	vec3 reflectDir = reflect(-lightDir, normal);

	float diff = max(dot(normal, lightDir), 0.0f);
	float spec = pow(max(dot(cameraDir, reflectDir), 0.0f), u_Material.shininess);

	vec3 ambient  = light.ambient         * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));

	return ambient + diffuse + specular;
}