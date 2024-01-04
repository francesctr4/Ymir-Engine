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
	
	uniform float time;
	uniform float speed;

	const vec3 lightDirection = normalize(vec3(1.0, 0.0, 1.0));

	void main()
	{
	 	// Compute dot product, clamp to ensure positive values only
  		float intensity = max(dot(Normal, lightDirection), 0.0);

    	// Normalized pixel coordinates (from 0 to 1)
    	vec2 uv = Position.xy;

    	// Time varying pixel color
    	vec3 col = 0.5 + 0.5 * cos(time * speed + uv.xyx + vec3(0,2,4));

    	// Output to screen
    	FragColor = vec4(intensity * col,1.0);
	}

#endif
