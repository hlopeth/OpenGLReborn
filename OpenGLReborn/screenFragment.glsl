#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D screenTextureLeft;
uniform sampler2D screenTextureRight;
uniform mat3 filterLeft;
uniform mat3 filterRight;

void main()
{
    vec3 colL = texture(screenTextureLeft, TexCoords).rgb;
    vec3 colR = texture(screenTextureRight, TexCoords).rgb;
    FragColor = vec4(filterLeft * colL + filterRight * colR, 1.0);
} 