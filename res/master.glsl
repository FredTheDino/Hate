#version 300 es
#define VERT
precision highp float;

uniform float t;

#ifdef VERT
layout(location=0) in highp vec2 in_pos;
layout(location=1) in highp vec2 in_texCoords;

out vec2 pass_texCoord;

void main() {
	gl_Position = vec4(in_pos.x, -in_pos.y, 0, 1);
	pass_texCoord = in_texCoords;
}
#endif 

#ifdef FRAG
out highp vec4 color;

in vec2 pass_texCoord;

void main() {
	color = vec4(sin(t) * 0.5 + 0.5, cos(t) * 0.5 + 0.5, 1, 1);
}
#endif


