// Basic "Earth" vertex shader, 2012
// Patrick Joos, Eduardo Hahn Paredes
#version 150 compatibility

void main()
{	
	gl_FrontColor  = gl_Color;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
	gl_Position    = ftransform();
}
