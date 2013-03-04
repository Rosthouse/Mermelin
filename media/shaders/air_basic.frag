// Basic "Air" fragment shader, 2012
// Patrick Joos, Eduardo Hahn Paredes
#version 150 compatibility

uniform sampler2D clouds_color;

void main()
{
	vec4 tex1 = texture2D(clouds_color, gl_TexCoord[0].st);
	vec4 tex2 = texture2D(clouds_color, gl_TexCoord[1].st);
	vec4 tex3 = texture2D(clouds_color, gl_TexCoord[2].st);
	gl_FragColor = tex1 * 0.25 + tex2 * 0.25 + tex3 * 0.25;
}