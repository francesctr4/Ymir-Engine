#version 450 core

#ifdef VERTEX_SHADER

	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aNormal;
	layout(location = 2) in vec2 aTexCoords;
	
	out vec3 Position;
	out vec3 Normal;
	
	uniform mat4 projection;
	uniform mat4 view;
	uniform mat4 model;

	void main()
	{
		Position = aPos;
		Normal = aNormal;
		
		gl_Position = projection * view * model * vec4(aPos, 1.0f);
	}

#endif 

#ifdef FRAGMENT_SHADER

	in vec3 Position;
	in vec3 Normal;

	out vec4 FragColor;
	
	uniform vec3 color;
	
	uniform bool light;
	uniform vec3 lightDir;

	void main()
	{
		float intensity = max(dot(Normal, normalize(lightDir)), 0.0);
		
		if (light) {
			FragColor = vec4(intensity * color, 1.0);
		}
		else {
			FragColor = vec4(color, 1.0);
		}
	}

#endif
