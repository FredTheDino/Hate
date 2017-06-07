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

layout(location=8) uniform highp mat4 projection;

layout(location=9) uniform bool use_lighting;
layout(location=10) uniform sampler2D color_map;
layout(location=11) uniform sampler2D normal_map;

layout(location=12) uniform int shader_type;

// Font stuff
layout(location=13) uniform float min_edge;
layout(location=14) uniform float max_edge;
layout(location=15) uniform vec4 text_color;


const int DEFAULT = 0;
const int TEXT_RENDER = 1;

#ifdef VERT
layout(location=0) in highp vec2 in_pos;
layout(location=1) in highp vec2 in_texCoord;

out vec2 pass_texCoord;

void default_render() {
	if (use_transform) {
		// TODO
		gl_Position = vec4(in_pos, 0.0, 1.0) * projection;
	} else {
		gl_Position = vec4(x + w * in_pos.x, y + h * in_pos.y, 0, 1.0) * projection;
	}

	pass_texCoord = in_texCoord;
}

void text_render() {
	vec2 pos;
	if (use_transform) {
		pos = (vec4(in_pos, 0.0, 1.0) * projection).xy;
	} else {
		pos = in_pos * mat2(projection);
	}

	gl_Position = vec4(pos, 0.0, 1.0);

	pass_texCoord = in_texCoord;
}

void main() {
	if (shader_type == DEFAULT) {
		default_render();
	} else if (shader_type == TEXT_RENDER) {
		text_render();
	}
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;

const vec3 lit = vec3(0.95, 0.0, 0.22);
const vec3 unlit = vec3(0.0, 0.01, 0.05);

vec3 get_normal(sampler2D tex, vec2 coord) {
	vec4 s = texture(tex, coord);
	vec3 normal = s.xyz;
	// We translate the normal.

	// @WTF!?
	// Why does this work?! Why is it 0.75 and not 0.5?
	float a = 0.75;
	normal -= vec3(a, a, a);
	normal = normalize(normal);

	// If the alpha is 0, so is the normal.
	return normal * s.w;
}

void default_render() {
	float speed = 2.0;
	vec3 light_dir = normalize(vec3(sin(t), cos(t), 0.0));
	//vec3 normal = normalize(vec3(pass_texCoord.x - 0.5, pass_texCoord.y - 0.5, 0.5));

	vec3 normal = get_normal(normal_map, pass_texCoord);
	float alpha = texture(normal_map, pass_texCoord).w;

	float lightness = dot(normal, light_dir);
	vec3 shaded = mix(unlit, lit, max(lightness, 0.0));
	
	if (alpha == 1.0) {
		color = vec4(shaded, 1.0);
	} else {
		color = vec4(1.0, 1.0, 1.0, 0.0);
	}
}

void text_render() {
	// TODO
	float dist = texture(color_map, pass_texCoord).w;
	float alpha = smoothstep(min_edge, max_edge, dist);
	color = vec4(text_color.xyz, text_color.w * alpha);
}

void main() {
	if (shader_type == DEFAULT) {
		default_render();
	} else if (shader_type == TEXT_RENDER) {
		text_render();
	}
}
#endif
