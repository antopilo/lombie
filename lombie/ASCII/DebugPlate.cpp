#include "DebugPlate.h"
#include "PlateRenderer.h"

DebugPlate::DebugPlate()
{
	_plate = std::make_shared<Plate>(16, 16);

	unsigned char c = 0;
	for (int y = 15; y >= 0; y--)
	{
		for (int x = 0; x < 16; x++)
		{
			_plate->SetChar(x, y, c);
			c++;
		}
	}
}

void DebugPlate::Draw()
{
	Matrix4 transform = Matrix4(1);
	transform = glm::scale(transform, Vector3(0.25f));

	PlateRenderer::Get().RenderPlate(*_plate.get(), transform, Matrix4(1), glm::ortho(0.0, 16.0, 0.0, 9.0, -1.0, 1.0));
}
