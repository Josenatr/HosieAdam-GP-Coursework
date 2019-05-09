//Version Number
#version 400

//The layout qualifers
layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 texCoord;
layout (location = 2) in vec3 VertexNormal;

out VS_OUT {
    vec2 texCoords;
} vs_out;

//Uniform variable
uniform mat4 transform;

void main()
{
	vs_out.texCoords = texCoord;

	// Sets the position of the current vertex
	gl_Position = transform * vec4(VertexPosition, 1.0);
}