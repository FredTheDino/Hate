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

layout(location=10) uniform sampler2D normal_map;


#ifdef VERT
layout(location=0) in highp vec2 in_pos;
layout(location=1) in highp vec2 in_texCoord;

out vec2 pass_texCoord;

void main() {
	if (use_transform) {
		// TODO
		gl_Position = vec4(in_pos, 0, 1.0);
	} else {
		gl_Position = vec4(x + w * in_pos.x, y - h * in_pos.y, 0, 1.0);
	}

	pass_texCoord = vec2(in_texCoord.x, in_texCoord.y);
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;

const vec3 lit = vec3(0.75, 0.1, 0.1);
const vec3 unlit = vec3(0.0, 0.01, 0.05);

vec3 get_normal(sampler2D tex, vec2 coord) {
	vec4 s = texture(tex, coord);
	vec3 normal = s.xyz;
	// We translate the normal
	normal -= vec3(0.5, 0.5, 0.5);
	normal = normal * 2.0;

	// If the alpha is 0, so is the normal.
	return normal * s.w;
}

void main() {
	float speed = 2.0;
	vec3 light_dir = normalize(vec3(sin(t), cos(t), 0.0));
	//vec3 normal = normalize(vec3(pass_texCoord.x - 0.5, pass_texCoord.y - 0.5, 0.5));

	vec3 normal = get_normal(normal_map, pass_texCoord);
	float alpha = texture(normal_map, pass_texCoord).w;

	float lightness = dot(normal, light_dir);
	vec3 shaded = mix(unlit, lit, max(lightness, 0.0));
	
	color = vec4(shaded, alpha);

	float a = normal.x * 0.5 + 0.5;
	if (abs(a - 0.5) <= 0.05)
		a = 0.0;
	float b = normal.y * 0.5 + 0.5;
	if (abs(b - 0.5) <= 0.05)
		b = 0.0;
	float c = normal.z * 0.5 + 0.5;
	if (abs(c - 0.5) <= 0.05)
		c = 0.0;
	color = vec4(a, b, c, alpha);
}
#endif
