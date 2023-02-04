#include "Plate.h"

#include <iostream>

Plate::Plate(uint32_t width, uint32_t height)
{
	_width = width;
	_height = height;

	// init data
	_data.reserve(width);
	for (int x = 0; x < width; x++)
	{
		_data.push_back(std::vector<Char>());
		_data[x].reserve(height);

		for (int y = 0; y < height; y++)
		{
			_data[x].push_back(Char(' '));
		}
	}
}

Plate::~Plate()
{
	// clear data
}

uint32_t Plate::GetWidth() const
{
	return _width;
}

uint32_t Plate::GetHeight() const
{
	return _height;
}

Char Plate::GetChar(uint32_t x, uint32_t y) const
{
	if (IsInside(x, y))
	{
		return _data[x][y];
	}

	std::cout << "Char outside of plate has been accessed!" << std::endl;

	return Char(' ');
}

void Plate::SetChar(uint32_t x, uint32_t y, Char data)
{
	if (IsInside(x, y))
	{
		_data[x][y] = data;
	}
}

bool Plate::IsInside(uint32_t x, uint32_t y) const
{
	return x < _width && y < _height;
}