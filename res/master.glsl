#version 300 es
#define VERT
precision highp float;

#ifdef VERT
layout(location=0) in highp vec3 in_pos;
layout(location=1) in highp vec2 in_texCoord;

out vec2 pass_texCoord;

void main() {
	vec3 pos = in_pos;

	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0);

	pass_texCoord = in_texCoord;
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;

void main() {
	color = vec4(pass_texCoord, 0.1, 1);
}
#endif
