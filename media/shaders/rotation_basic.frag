// Basic "Rotation" fragment shader, 2012
// Patrick Joos, Eduardo Hahn Paredes
#version 150 compatibility

uniform sampler2D texture;
in vec4 texCoord;

void main()
{
    gl_FragColor = texture2D(texture, vec2(texCoord.s, texCoord.t), texCoord.w);
}
