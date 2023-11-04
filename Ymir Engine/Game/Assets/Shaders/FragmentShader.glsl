#version 460 core

out vec4 FragColor;

in vec2 TexCoords;
in vec3 Normal;

uniform sampler2D texture_diffuse1;
uniform bool displayNormalMap; // Boolean uniform to toggle between normal visualization and texture display

void main()
{   
    if (displayNormalMap) {

        // Normalize the interpolated normal since it's interpolated across the surface
        vec3 norm = normalize(Normal);
    
        // Adjust the normalized normal to be in the range [0, 1] for visualization purposes
        vec3 color = 0.5 * (norm + vec3(1.0));
    
        FragColor = vec4(color, 1.0);

    } else {

        FragColor = texture(texture_diffuse1, TexCoords);

    }
}