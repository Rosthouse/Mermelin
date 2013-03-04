// Basic "Earth" fragment shader, 2012
// Patrick Joos, Eduardo Hahn Paredes
#version 150 compatibility

uniform sampler2D dirt_color;

void main()
{
	gl_FragColor = texture2D(dirt_color, gl_TexCoord[0].st);
}
