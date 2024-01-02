#version 450 core

#ifdef VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform float speed;
float timer;

out float height;
out float depth;
out float peak;

void main(){

	vec3 pos = aPos;
	
	timer = time * speed;
	
	pos.z += 0.2 * sin(pos.y + (timer * 0.8));
	pos.z += 0.4 * sin(pos.x * 0.5 + (timer * 2));
	peak = pos.z;
	
	pos.z += 0.6 * sin(pos.y * 0.1 + (timer * 3));
	
	gl_Position = projection * view * model * vec4(pos.xyz, 1.0);
	
	// Variable settings

	depth = gl_Position.z;
	height = pos.z;
	TexCoords = aTexCoords;
	Normal = aNormal;

}

#endif

#ifdef FRAGMENT_SHADER

in vec2 TexCoords;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

in float height;
in float depth;
in float peak;

vec4 color = vec4(0.1, 0.2, 0.4, 1.0);

void main(){

	color += vec4(0.2, 0.2, 0.3, 0.0) * height;
	color -= -peak * 0.05;
	
	color -= 0.2;
	
	FragColor = texture(texture_diffuse1, TexCoords) * 0.6 + color; // - (0.003 * depth);

}

#endif



