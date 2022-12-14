#version 110
uniform mat4 MVP;
attribute vec2 aPos;
attribute vec3 vCol;
varying vec3 color;

void main()
{
	gl_Position = MVP * vec4(aPos, 0.0, 1.0);
	color = vCol;
}
