#version 330 core

out vec4 FragColor;
in vec3 vertexColor;

uniform vec3 offset_color;
uniform float rate=1.0;

void main() {
    FragColor = vec4(sin(vertexColor.x + offset_color.x) / 2 + 0.5,cos(vertexColor.y + offset_color.y) / 2 + 0.5,cos(vertexColor.z + offset_color.z) / 2 + 0.4, rate);
}