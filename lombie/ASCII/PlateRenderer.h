#pragma once
#include "Plate.h"

#include <NuakeRenderer/Shader.h>
#include <NuakeRenderer/Math.h>
#include <NuakeRenderer/VertexArray.h>
#include <NuakeRenderer/VertexBuffer.h>
#include <NuakeRenderer/Texture.h>

class PlateRenderer
{
private:
	PlateRenderer();
	~PlateRenderer();

	std::shared_ptr<NuakeRenderer::Shader> _asciiShader;
	std::shared_ptr<NuakeRenderer::VertexArray> _vertexArray;
	std::shared_ptr<NuakeRenderer::VertexBuffer> _vertexBuffer;
	std::shared_ptr<NuakeRenderer::Texture> _bitmap;
	std::shared_ptr<NuakeRenderer::Texture> _bitmapHalf;
public:
	static PlateRenderer& Get();

	void RenderPlate(const Plate& plate, const Matrix4& transform, const Matrix4& view, const Matrix4& projection, const Vector2& from = Vector2(0 , 0), const Vector2& to = Vector2(-1, -1));
	void RenderChar(const Char& data, const Matrix4& transform);

	void RenderPlateHalf(const Plate& plate, const Matrix4& transform, const Matrix4& view, const Matrix4& projection, const Vector2& from = Vector2(0, 0), const Vector2& to = Vector2(-1, -1));
	void RenderCharHalf(const Char& data, const Matrix4& transform);
};