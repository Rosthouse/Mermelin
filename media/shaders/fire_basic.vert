// Basic "Fire" vertex shader, 2012
// Patrick Joos, Eduardo Hahn Paredes
#version 150 compatibility

out float noise;

float rand(vec4 co){
    return fract(sin(dot(co.xy ,vec2(12.9898,78.233))) * 43758.5453);
}

void main()
{
	gl_Position = ftransform();
	noise = rand(gl_Vertex);
}
