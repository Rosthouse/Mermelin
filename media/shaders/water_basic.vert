// simple vertex shader
#version 150 compatibility

uniform float time;
in vec2 waveSpeed;
out vec3 vTexCoord;

void main()
{
	//get multitexturing coords
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord1;

	//Move the water
	gl_TexCoord[0].x += time * waveSpeed.x;
	gl_TexCoord[0].y += time * waveSpeed.y;

	gl_TexCoord[1].x -= time * waveSpeed.x;
	gl_TexCoord[1].y -= time * waveSpeed.y;

	gl_Position = ftransform();
}
