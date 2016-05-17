#version 330 core

//VERTEX SHADER

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec2 textureCoords;
out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightPosition;

void main()
{
    vec4 worldPosition =  model * vec4(position, 1.0f);
    gl_Position = projection * view * worldPosition;
    textureCoords = vec2(texCoords.x, 1.0 - texCoords.y);

    surfaceNormal = (model * vec4(normal, 0.0)).xyz;
    toLightVector = lightPosition - worldPosition.xyz;
    toCameraVector = (inverse(view) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - worldPosition.xyz;
}