#include "UIPlate.h"
#include "PlateRenderer.h"

UIPlate::UIPlate(const Vector2& position, uint32_t width, uint32_t height)
{
	_plate = std::make_shared<Plate>(width, height);
	_position = position;

	Char corner = Char('+');
	_plate->SetChar(0, 0, corner);
	_plate->SetChar(width - 1, 0, (char)175);
	_plate->SetChar(0, height - 1, corner);
	_plate->SetChar(width - 1, height - 1, corner);

	for (int x = 1; x < width - 1; x++)
	{
		_plate->SetChar(x, 0, Char((char)180));
		_plate->SetChar(x, height - 1, Char((char)180));
	}

	for (int y = 1; y < height - 1; y++)
	{
		_plate->SetChar(0, y, Char((char)163));
		_plate->SetChar(width - 1, y, Char((char)163));
	}
}

void UIPlate::Draw()
{
	Matrix4 transform = Matrix4(1);
	transform = glm::scale(transform, Vector3(0.25f));
	transform = glm::translate(transform, Vector3(_position.x, _position.y, 0.1f));

	PlateRenderer::Get().RenderPlate(*_plate.get(), transform, Matrix4(1), glm::ortho(0.0, 16.0, 0.0, 9.0, -1.0, 1.0));
}