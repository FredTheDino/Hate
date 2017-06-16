#version 310 es
#define VERT
precision highp float;

layout(location=0) uniform highp float t;

layout(location=1) uniform bool use_transform;
layout(location=16) uniform bool translate_projection;
// If use_transform is false
layout(location=2) uniform highp float x;
layout(location=3) uniform highp float y;
layout(location=4) uniform highp float w;
layout(location=5) uniform highp float h;
// If use_transform is true
layout(location=6) uniform highp mat4 transform;
layout(location=7) uniform highp mat4 world;

layout(location=8) uniform highp mat4 projection;

layout(location=17) uniform highp int texture_mode; // 0 = color, 1 = color_map, 2 = normal_map. Or them.
layout(location=19) uniform vec2 sprites;
layout(location=20) uniform highp int sprite_id;
layout(location=10) uniform sampler2D color_map;
layout(location=11) uniform sampler2D normal_map;
layout(location=18) uniform vec4 draw_color; // = vec4(1.0, 1.0, 1.0, 1.0);

layout(location=12) uniform highp int shader_type;

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
	mat4 m = projection;

	if (translate_projection) {
		m = world + m;
	} else {
		m[3][3] = 1.0f;
	}

	if (use_transform) {
		m = transform * m;
	}

	if (use_transform) {
		gl_Position = vec4(in_pos, 0.0, 1.0) * m;
	} else {
		gl_Position = vec4(x + w * in_pos.x, y + h * in_pos.y, 0.0, 1.0) * m;
	}

	float tex_w = 1.0 / sprites.x;
	float tex_h = 1.0 / sprites.y;
	pass_texCoord = vec2(
		tex_w * (in_texCoord.x + float(int(sprite_id) % int(sprites.y))), 
		tex_h * (in_texCoord.y + float(floor(float(sprite_id) / float(sprites.x)))));
	
	pass_texCoord = in_texCoord;

	//Something is wrong, the monkey doesn't show up and I don't know why.
}

void text_render() {
	vec4 pos;
	if (translate_projection) {
		pos = vec4(in_pos, 0.0, 1.0) * (projection + world);
	} else {
		pos = vec4(in_pos * mat2(projection), 0.0, 1.0);
	}

	gl_Position = pos;

	pass_texCoord = in_texCoord;
}

void main() {
	if (shader_type == DEFAULT) {
		default_render();
	} else if (shader_type == TEXT_RENDER) {
		text_render();
	} else {
		gl_Position = vec4(in_pos, 0.0, 1.0);
	}
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;

const vec3 unlit = vec3(0.4, 0.4, 0.5);

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
	// PLACE HOLDER!
	float speed = 2.0;
	vec3 light_dir = normalize(vec3(sin(t), cos(t), 0.0));

	if (texture_mode == 0) {
		// Plain color:
		color = draw_color;
	} else {
		// Just set it to something by default.
		vec4 lit;

		// We're using textures so we need to get more funky
		if (bool(texture_mode & 1)) {
			// We're using a color texture.
			lit = texture(color_map, pass_texCoord);
		} else {
			lit = draw_color;
		}

		if (bool(texture_mode & 2)) {
			// Hello normalmap!
			vec3 normal = get_normal(normal_map, pass_texCoord);
			float lightness = dot(normal, light_dir);
			color = vec4(mix(unlit * lit.xyz, lit.xyz, lightness), lit.w);
		} else {
			color = lit;
		}
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
