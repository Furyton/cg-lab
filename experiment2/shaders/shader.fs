#version 330 core

out vec4 FragColor;
in vec3 tangent;
in vec3 light;

uniform vec3 offset_color;
uniform float rate=1.0;

void main() {
    // FragColor = vec4(sin(vertexColor.x + offset_color.x) / 2 + 0.5,cos(vertexColor.y + offset_color.y) / 2 + 0.5,cos(vertexColor.z + offset_color.z) / 2 + 0.4, rate);
    // FragColor = vec4(vec3(1.0) * dot(tangent, normalize(light)), 1.0);
    FragColor = vec4(vec3((dot(normalize(tangent), normalize(light))) * dot(normalize(tangent), normalize(light))  * dot(normalize(tangent), normalize(light)) * dot(normalize(tangent), normalize(light))), 1.0);
    // FragColor = vec4(vec3(1.0), 1.0);
}