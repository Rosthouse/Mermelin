// Basic "Fire" fragment shader, 2012
// Patrick Joos, Eduardo Hahn Paredes
#version 150 compatibility

uniform vec4 startColor;
uniform vec4 endColor;
uniform float time;

in float noise;
out vec4 color;

void main()
{
	float lerpValue = abs( sin(time) + noise );
	color = mix(startColor, endColor, lerpValue);
}
