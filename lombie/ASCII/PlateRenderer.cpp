#include "PlateRenderer.h"
#include "../Core/FileSystem.h"

#include <NuakeRenderer/ShaderRegistry.h>

using namespace NuakeRenderer;

struct Vertex
{
	Vector3 Pos;
	Vector2 Uv;
};

PlateRenderer& PlateRenderer::Get()
{
	static PlateRenderer instance;
	return instance;
}

PlateRenderer::PlateRenderer()
{
	// Initialize shaders
	std::string vert = FileSystem::ReadFile("resources/shaders/ascii.vert.glsl");
	std::string frag = FileSystem::ReadFile("resources/shaders/ascii.frag.glsl");

	_asciiShader = std::make_shared<Shader>(vert, frag);
	ShaderRegistry::Set("default_ascii", _asciiShader.get());

	const std::vector<Vertex> vertices = {
		{ { 1.f,  1.f, 0.f }, { 1.f, 0.f } },
		{ { 1.f,  0.f, 0.f }, { 1.f, 1.f } },
		{ { 0.f,  1.f, 0.f }, { 0.f, 0.f } },
		{ { 1.f,  0.f, 0.f }, { 1.f, 1.f } },
		{ { 0.f,  0.f, 0.f }, { 0.f, 1.f } },
		{ { 0.f,  1.f, 0.f }, { 0.f, 0.f } },
	};

	_vertexArray = std::make_shared<NuakeRenderer::VertexArray>();
	_vertexArray->Bind();
	_vertexBuffer = std::make_shared<NuakeRenderer::VertexBuffer>(vertices.data(), (unsigned int)(vertices.size() * sizeof(Vertex)));

	auto vbl = NuakeRenderer::VertexBufferLayout();
	vbl.Push<float>(3); // Position
	vbl.Push<float>(2); // UV

	_vertexArray->AddBuffer(*_vertexBuffer, vbl);
	_vertexArray->Unbind();
	
	// Loading bitmap
	const std::string imgPath = "resources/fonts/cp437_12x12.png";

	NuakeRenderer::TextureFlags textureFlags;
	textureFlags.magFilter = SamplerFilter::NEAREST;
	textureFlags.minFilter = SamplerFilter::NEAREST;
	_bitmap = std::make_shared<NuakeRenderer::Texture>(textureFlags, imgPath);
}

PlateRenderer::~PlateRenderer()
{
}

void PlateRenderer::RenderPlate(const Plate& plate, const Matrix4& transform, const Matrix4& view)
{
	using namespace NuakeRenderer;
	_asciiShader->Bind();
	_asciiShader->SetUniform("u_View", view);

	_bitmap->Bind(1);
	_asciiShader->SetUniform("u_Bitmap", 1);
	
	_vertexArray->Bind();


	//Matrix4 transform2 = glm::scale(transform, Vector3(10, 10, 10));
	for (int x = 0; x < plate.GetWidth(); x++)
	{
		Matrix4 rowTransform = glm::translate(transform, Vector3(x, 0, 0));
		for (int y = 0; y < plate.GetHeight(); y++)
		{
			Matrix4 cellTransform = glm::translate(rowTransform, Vector3(0, y, 0));
			_asciiShader->SetUniform("u_Model", cellTransform);

			const Char& data = plate.GetChar(x, y);
			int asciiIndex = (int)data.GetData();

			_asciiShader->SetUniform("u_fgColor", data.GetFgColor());
			_asciiShader->SetUniform("u_bgColor", data.GetBgColor());
			_asciiShader->SetUniform("u_Char", asciiIndex);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
}

void PlateRenderer::RenderChar(const Char& data, const Matrix4& transform, const Matrix4& view)
{
	using namespace NuakeRenderer;
	_asciiShader->Bind();
	_asciiShader->SetUniform("u_View", view);

	_bitmap->Bind(1);
	_asciiShader->SetUniform("u_Bitmap", 1);

	_vertexArray->Bind();
	int asciiIndex = (int)data.GetData();
	_asciiShader->SetUniform("u_fgColor", data.GetFgColor());
	_asciiShader->SetUniform("u_bgColor", data.GetBgColor());
	_asciiShader->SetUniform("u_Char", asciiIndex);

	_vertexArray->Bind();
	glDrawArrays(GL_TRIANGLES, 0, 6);
}