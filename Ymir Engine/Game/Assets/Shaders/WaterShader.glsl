#version 450 core

#ifdef VERTEX_SHADER

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec2 TexCoords;
out vec3 Normal;

out float height;
out float peak;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform float time;
uniform float speed;

float timer;

void main(){

	vec3 pos = aPos;
	
	Normal = aNormal;
	TexCoords = aTexCoords;

	timer = time * speed;
	
	// Modify the position based on time and speed using sinusoidal functions

	pos.z += 0.2 * sin(pos.y + (timer * 0.8));
	pos.z += 0.4 * sin(pos.x * 0.5 + (timer * 2));
	pos.z += 0.6 * sin(pos.y * 0.1 + (timer * 3));
	
	// Send height and peak values to the fragment shader
	
	height = peak = pos.z;

	// Calculate final position in clip space

	gl_Position = projection * view * model * vec4(pos.xyz, 1.0);
}

#endif

#ifdef FRAGMENT_SHADER

in vec2 TexCoords;
in vec3 Normal;

in float height;
in float peak;

out vec4 FragColor;

uniform sampler2D texture_diffuse1;

vec4 color = vec4(0.1, 0.2, 0.4, 1.0);

void main(){

	// Combine texture and color based on height and peak information

	color += vec4(0.2, 0.2, 0.3, 0.0) * height;
	color -= -peak * 0.05;
	color -= 0.2;

	// Combine final color using the received diffuse texture
	
	FragColor = texture(texture_diffuse1, TexCoords) * 0.6 + color;
}

#endif