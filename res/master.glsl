#version 300 es
#define VERT
precision highp float;

uniform float t;

#ifdef VERT
layout(location=0) in highp vec3 in_pos;
layout(location=1) in highp vec3 in_normal;
layout(location=2) in highp vec2 in_texCoord;

out vec2 pass_texCoord;
out vec3 pass_normal;

void main() {
	float c = cos(t * 1.0);
	float s = sin(t * 1.0);
	vec3 pos;
	pos.x = in_pos.x * c - in_pos.z * s;
	pos.y = in_pos.y;
	pos.z = in_pos.x * s + in_pos.z * c;
	pos.x *= 9.0 / 16.0;


	gl_Position = vec4(pos * 0.75, 1);
	pass_texCoord = in_texCoord;

	vec3 nor;
	nor.x = in_normal.x * c - in_normal.z * s;
	nor.z = in_normal.x * s + in_normal.z * c;
	nor.y = in_normal.y;
	pass_normal = nor;
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;
in vec3 pass_normal;
const vec4 diffuse = vec4(0.75, 0.2, 0.0, 1.0);
const vec4 specular = vec4(0.9, 0.5, 0.2, 1.0);
const vec4 ambient = vec4(0, 0, 0.1, 1.0);
const float shine = 16.0;
const vec3 lightDir = vec3(-10.0, 10.0, -10.0);

void main() {
//	color = vec4(sin(t) * 0.5 + 0.5, cos(t) * 0.5 + 0.5, 1, 1);

	vec3 light = normalize(lightDir);

	float lumminosity = max(dot(light, pass_normal), 0.0);
	
	float specularity = 0.0;
	if (lumminosity > 0.0) {
		float phong = max(dot(normalize(lightDir + vec3(0, 0, 1)), pass_normal), 0.0);
		specularity = max(pow(phong, shine), 0.0);
	}

	color = ambient + diffuse * lumminosity + specular * specularity;
}
#endif


