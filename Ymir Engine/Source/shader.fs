#version 330 core

in vec3 FragPos; // Input position from vertex shader
in vec3 Normal;  // Input normal from vertex shader
in vec2 TexCoord; // Input texture coordinates from vertex shader

out vec4 FragColor; // Output color

uniform sampler2D texture_diffuse; // Diffuse texture

void main() {
    // Lighting calculations (e.g., Phong shading)
    vec3 ambientColor = vec3(0.1, 0.1, 0.1);
    vec3 lightColor = vec3(1.0, 1.0, 1.0);
    vec3 lightPos = vec3(0.0, 0.0, 2.0); // Example light position

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    // Sample the diffuse texture
    vec3 textureColor = texture(texture_diffuse, TexCoord).rgb;

    // Final color (ambient + diffuse + texture)
    vec3 result = (ambientColor + diffuse) * textureColor;

    FragColor = vec4(result, 1.0);
}
