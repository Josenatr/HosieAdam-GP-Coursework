#version 400

uniform mat4 u_pm;
uniform mat4 u_vm;
uniform vec3 cameraPos;
uniform samplerCube skybox;
uniform float c_counter;

uniform float r_change;
uniform float g_change;
uniform float b_change;

uniform float refraction;

uniform float gammaChange;

layout( location = 0 ) out vec4 fragcolor;
 
in vec3 v_norm;
in vec3 v_pos; 

void main() {
 
	float ratio = 1.00 / refraction;
	vec3 i = normalize(v_pos - cameraPos);
    vec3 r = refract(i, normalize(v_norm), ratio);

	vec4 clipPos = vec4(v_pos, 1.0);
	vec3 n = normalize(mat3(u_vm) * v_norm);      // convert normal to view space
	vec3 p = vec3((u_pm) * clipPos);                // position in clip space
	vec3 v = normalize(p);                        // normalised eye vector
	float vdn = 0.6 - max(dot(v, n), 0.0);        // the rim contribution
	
	float intensity;
	vec4 color;
	intensity = 0.0 + c_counter;

	color = vec4(intensity-r_change,intensity- g_change,intensity- b_change,1.0);

	float gamma = gammaChange;

  fragcolor.a = 0.9;
  fragcolor.rgb = vec3(texture(skybox, r).rgb + smoothstep(0.4, 0.8, vdn) + vec3(color.x,color.y,color.z));
  fragcolor.rgb = pow(fragcolor.rgb, vec3(1.0/gamma));
}