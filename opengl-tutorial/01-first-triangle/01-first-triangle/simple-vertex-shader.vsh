#version 330 core

// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 vertexPosition;

void main() {
    gl_Position = vec4(vertexPosition.x,
                       vertexPosition.y,
                       vertexPosition.z,
                       1.0);
}
