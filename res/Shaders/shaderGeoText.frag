//Version number
#version 400
//Layout Qualifer

layout( location = 0 ) out vec4 fragcolor;

//Uniform variables

//uniform float randColourX;
//uniform float randColourY;
//uniform float randColourZ;
  uniform sampler2D diffuse;

	in vec2 TexCoords;


void main()
{
	 fragcolor = vec4(texture(diffuse, TexCoords));
}