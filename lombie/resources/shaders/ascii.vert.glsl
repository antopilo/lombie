#version 460 core

layout(location = 0) in vec3 Position;
layout(location = 1) in vec2 UV;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec2 v_UV;

void main() {
	v_UV = vec2(int(UV.x), int(UV.y));

	gl_Position = u_Projection * u_View * u_Model * vec4(Position, 1.0f);
}