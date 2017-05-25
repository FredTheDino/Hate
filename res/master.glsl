#version 300 es
#define VERT
precision highp float;

#ifdef VERT
in vec4 position;
out vec4 out_position;

void main() {
	//
	out_position = position;
}
#endif 

#ifdef FRAG
out vec4 color;

void main() {
	color = vec4(1, 1, 1, 1);
}
#endif


