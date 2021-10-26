#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 tangent;
out vec3 light;

vec4 pos;

uniform float u_time;

uniform mat4 model = mat4(1.0);
uniform mat4 view = mat4(1.0);
uniform mat4 projection = mat4(1.0);

void main() {
    pos = vec4(aPos / 10.0, 1.0);
    pos -= vec4(0.0, 0.5, 0.0, 0.0);
    pos = view * model * pos;
    gl_Position = projection * pos;
    tangent = (projection * view * model * vec4(aNormal, 0.0)).xyz;
    light = (projection * view * (vec4(99.0, 99.0, 99.0, 1.0) - pos)).xyz;
}