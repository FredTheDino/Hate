#version 310 es
#define VERT
precision highp float;

layout(location=0) uniform highp float t;

layout(location=1) uniform bool use_transform;
// If use_transform is false
layout(location=2) uniform highp float x;
layout(location=3) uniform highp float y;
layout(location=4) uniform highp float w;
layout(location=5) uniform highp float h;
// If use_transform is true
layout(location=6) uniform highp mat4 transform;
layout(location=7) uniform highp mat4 world;

//layout(location=8) uniform


#ifdef VERT
layout(location=0) in highp vec2 in_pos;
layout(location=1) in highp vec2 in_texCoord;

out vec2 pass_texCoord;

void main() {
	if (use_transform) {
		// TODO
		gl_Position = vec4(in_pos, 0, 1.0);
	} else {
		gl_Position = vec4(x + w * in_pos.x, y + h * in_pos.y, 0, 1.0);
	}

	pass_texCoord = in_texCoord;
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;

const vec3 lit = vec3(0.9, 0.9, 0.85);
const vec3 unlit = vec3(0.0, 0.0, 0.1);

void main() {
	vec3 light_dir = normalize(vec3(cos(t), sin(t), 0.0));
	vec3 normal = normalize(vec3(pass_texCoord.x - 0.5, pass_texCoord.y - 0.5, 0.5));
	vec3 temp = mix(unlit, lit, max(dot(normal, light_dir), 0.0));
	
	color = vec4(temp, 1.0);
}
#endif
