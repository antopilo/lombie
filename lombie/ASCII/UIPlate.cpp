#include "UIPlate.h"
#include "PlateRenderer.h"
#include "../Core/Globals.h"

#include <iostream>

Zone::Zone(int startx, int endx, int starty, int endy)
{
	x = startx;
	xx = endx;
	y = starty;
	yy = endy;
}

bool Zone::IsInside(int mx, int my)
{
	return mx >= x && my >= y && mx <= xx && my <= yy;
}

UIPlate::UIPlate(const Vector2& position, uint32_t width, uint32_t height)
{
	_plate = std::make_shared<Plate>(width, height);
	_position = position;

	const std::string title = "/ Info /";

	Char corner = Char(176);
	_plate->SetChar(0, 0, 192);
	_plate->SetChar(width - 1, 0, 217);
	_plate->SetChar(0, height - 1, 218);
	_plate->SetChar(width - 1, height - 1, 191);

	for (int x = 1; x < width - 1; x++)
	{
		_plate->SetChar(x, 0, Char(196));
		_plate->SetChar(x, height - 1, Char(196));
	}

	for (int y = 1; y < height - 1; y++)
	{
		_plate->SetChar(0, y, Char(179));
		_plate->SetChar(width - 1, y, Char(179));
	}

	int center = width / 2;
	int halfTitle = title.size() / 2;
	int startX = center - halfTitle;
	int endX = center + halfTitle;
	for (int i = 0; i < width; i++)
	{
		int charIdx = i - startX;
		
		if (charIdx >= 0 && charIdx < title.size())
		{
			_plate->SetChar(i, height - 1, Char(title[charIdx]));
		}
	}
}

void UIPlate::Draw()
{
	Matrix4 transform = Matrix4(1);
	transform = glm::scale(transform, Vector3(Globals::TileSize));
	transform = glm::translate(transform, Vector3(_position.x, _position.y, 0.1f));

	PlateRenderer::Get().RenderPlateHalf(*_plate.get(), transform, Matrix4(1), glm::ortho(0.0, 16.0, 0.0, 9.0, -1.0, 1.0));
}

bool UIPlate::AcceptInput(float mx, float my)
{
	float xToCorner = mx - _position.x;
	float yToCorner = my - _position.y;
	//std::cout << "xToC: " << xToCorner << "yToC: " << yToCorner << std::endl;
	bool isInside = xToCorner > 0 && yToCorner > 0 && mx < (_position.x + _plate->GetWidth() / 2.0) && my < (_position.y + _plate->GetHeight());

	if (!isInside)
	{
		for (auto& z : _zones)
		{
			z.second._state = ZoneState::Idle;
		}
	}
	return isInside;
}

void UIPlate::Hover(int mx, int my)
{
	for (auto& z : _zones)
	{
		if (z.second.IsInside(mx, my))
		{
			z.second._state = ZoneState::Hover;
		}
		else
		{
			z.second._state = ZoneState::Idle;
		}
	}

	std::cout << "Hovered tile in ui: " << std::to_string(mx) << ", " << std::to_string(my) << std::endl;
}

std::shared_ptr<Plate> UIPlate::GetPlate()
{
	return _plate;
}

Vector2 UIPlate::GetPosition() const
{
	return _position;
}