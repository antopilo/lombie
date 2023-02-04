#version 460 core

in vec2 v_UV;
out vec4 FragColor;

uniform sampler2D u_Bitmap;
uniform int u_Char;
uniform vec4 u_fgColor;
uniform vec4 u_bgColor;

void main()
{
	int coordsX = u_Char % 16;
	int coordsY = u_Char / 16;
	vec2 uv = vec2(coordsX, coordsY) / vec2(16, 16);

	vec2 textureRes = textureSize(u_Bitmap, 0);
	vec2 cellSize = textureRes / vec2(16.0f);

	vec2 finalUv = mix(uv, uv + vec2(1.0/16.0), v_UV);
	float bitmapSample = texture(u_Bitmap, finalUv).r;
	FragColor = mix(u_bgColor, u_fgColor, bitmapSample);
}