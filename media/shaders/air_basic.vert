// Basic "Air" vertex shader, 2012
// Patrick Joos, Eduardo Hahn Paredes
#version 150 compatibility

uniform float time;

mat4 rotationMatrix(float Angle){
	return mat4(cos( Angle ), -sin( Angle ), 0.0, 0.0,
			    sin( Angle ),  cos( Angle ), 0.0, 0.0,
			    0.0,           0.0, 		 1.0, 0.0,
				0.0,           0.0, 		 0.0, 1.0);
}

void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_TexCoord[1] = gl_MultiTexCoord0 * rotationMatrix(time);
	gl_TexCoord[2] = gl_MultiTexCoord0 * rotationMatrix(time * 2.0);
}
