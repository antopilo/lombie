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
public:
	static PlateRenderer& Get();

	void RenderPlate(const Plate& plate, const Matrix4& transform, const Matrix4& view);
	void RenderChar(const Char& data, const Matrix4& transform, const Matrix4& view);
};