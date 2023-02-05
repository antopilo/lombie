#pragma once
#include "Plate.h"

#include <memory>

class UIPlate
{
private:
	std::shared_ptr<Plate> _plate;
	Vector2 _position;
public:
	UIPlate(const Vector2& position, uint32_t width, uint32_t height);

	void Draw();

	std::shared_ptr<Plate> GetPlate();
};