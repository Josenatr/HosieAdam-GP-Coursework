//Version number
#version 330 core

//Layout qualfier
layout (triangles) in;
layout (triangle_strip, max_vertices = 6) out;

in VS_OUT
{
	vec3 normal;
}gs_in[];

const float mag = 0.4; //mag represents the magnitude

void LineGeneration(int index)
{
	gl_Position = gl_in[index].gl_Position;
	EmitVertex();
	gl_Position = gl_in[index].gl_Position + vec4(gs_in[index].normal, 0,0) * mag;
	EmitVertex();
	EndPrimitve();
}

void main()
{
	LineGeneration(0);
	LineGeneration(1);
	LineGeneration(2);
}