#version 330 core

layout(location = 0) in vec3 inPosition; // Vertex position attribute
layout(location = 1) in vec3 inNormal;   // Vertex normal attribute
layout(location = 2) in vec2 inTexCoord; // Texture coordinate attribute

out vec3 FragPos; // Output position for fragment shader
out vec3 Normal;  // Output normal for lighting calculations
out vec2 TexCoord; // Output texture coordinates for texturing

uniform mat4 model;      // Model matrix
uniform mat4 view;       // View matrix
uniform mat4 projection; // Projection matrix

void main() {
    // Apply transformations: model -> view -> projection
    mat4 mvp = projection * view * model;
    gl_Position = mvp * vec4(inPosition, 1.0);

    // Pass data to the fragment shader
    FragPos = vec3(model * vec4(inPosition, 1.0));
    Normal = mat3(transpose(inverse(model))) * inNormal;
    TexCoord = inTexCoord;
}