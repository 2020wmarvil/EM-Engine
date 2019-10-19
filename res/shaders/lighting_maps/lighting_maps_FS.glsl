// fragment shader

#version 330 core

struct Material {
	sampler2D diffuse, specular, emission;
    float shininess;
}; 

struct Light {
    vec3 ambient, diffuse, specular;
    vec3 position, direction;
	float cutOff, outerCutOff;
	float constant, linear, quadratic;
};

in vec3 v_Normal;
in vec3 v_Color;
in vec2 v_TexCoord;
in vec3 v_FragPos;

layout(location = 0) out vec4 color;

uniform vec3 cameraPos;
uniform mat4 u_View;
uniform Material u_Material;
uniform Light u_Light;

uniform float u_Time;

uniform sampler2D u_Texture;

void main() {
//	vec3 lightPos = vec3(u_View * vec4(u_Light.position, 1.0));
	vec3 lightDir = normalize(u_Light.position - v_FragPos);

	float theta     = dot(lightDir, normalize(-u_Light.direction));
	float epsilon   = u_Light.cutOff - u_Light.outerCutOff;
	float intensity = clamp((theta - u_Light.outerCutOff) / epsilon, 0.0, 1.0);

	// ambient
	vec3 ambientLight = u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));

	// diffuse
	vec3 normal       = normalize(v_Normal);
	float diffuse     = max(dot(normal, lightDir), 0.0f);
	vec3 diffuseLight = u_Light.diffuse * diffuse * vec3(texture(u_Material.diffuse, v_TexCoord));

	// specular
	vec3 cameraDir     = normalize(cameraPos - v_FragPos);
	vec3 reflectDir    = reflect(-lightDir, normal);
	float specular     = pow(max(dot(cameraDir, reflectDir), 0.0f), u_Material.shininess);
	vec3 specularLight = u_Light.specular * specular * vec3(texture(u_Material.specular, v_TexCoord));

	// attenuation
	float distance    = length(u_Light.position - v_FragPos);
	float attenuation = 1.0f / (distance * distance * u_Light.quadratic + distance * u_Light.linear + u_Light.constant);

	diffuseLight  *= attenuation;
	specularLight *= attenuation;

	diffuseLight  *= intensity;
	specularLight *= intensity;

	vec3 resultantColor = ambientLight + diffuseLight + specularLight;

//	color = texColor * vec4(v_Color, 1.0f) * vec4(resultantColor, 1.0f);
	color = vec4(resultantColor, 1.0f);
}
