#version 300 es
#define VERT
precision highp float;

uniform float t;

uniform mat4 projection;
uniform mat4 world;
uniform mat4 model;

uniform sampler2D diffuse;
uniform sampler2D specular;
uniform sampler2D normal;

#ifdef VERT
layout(location=0) in highp vec3 in_pos;
layout(location=1) in highp vec3 in_normal;
layout(location=2) in highp vec2 in_texCoord;

out vec2 pass_texCoord;
out vec3 pass_normal;
out vec3 cam_pos;

void main() {
	cam_pos = vec3(projection[0][3], projection[1][3], projection[2][3]); 
	mat4 transform = model * world * projection;

	//transform = mat4(1);

	vec3 pos = in_pos;

	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0) * transform;

	pass_texCoord = in_texCoord * t;

	pass_normal = in_normal * mat3(model);
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;
in vec3 pass_normal;
in vec3 cam_pos;

const vec4 d = vec4(0.75, 0.2, 0.0, 1.0);
const vec4 s = vec4(0.9, 0.5, 0.2, 1.0);
const vec4 a = vec4(0, 0, 0.1, 1.0);
const float shine = 1.0;
const vec3 lightDir = vec3(-10.0, 10.0, 0.0);

void main() {
//	color = vec4(sin(t) * 0.5 + 0.5, cos(t) * 0.5 + 0.5, 1, 1);

	vec3 light = normalize(lightDir);

	float lumminosity = max(dot(light, pass_normal), 0.0) * (sin(t) * 0.1 + 1.0);
	
	float specularity = 0.0;
	if (lumminosity > 0.0 && false) {
		float phong = max(dot(normalize(lightDir + cam_pos), pass_normal), 0.0);
		specularity = pow(phong, shine);
	}
	color = a + d * lumminosity + s * specularity;
}
#endif


