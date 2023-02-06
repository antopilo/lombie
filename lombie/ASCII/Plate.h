#pragma once
#include "Char.h"

#include <memory>
#include <string>
#include <vector>

class Plate
{
private:
	uint32_t _width;
	uint32_t _height;

	std::vector<std::vector<Char>> _data;
public:
	Plate(uint32_t width, uint32_t height);
	~Plate();

	uint32_t GetWidth() const;
	uint32_t GetHeight() const;

	Char GetChar(uint32_t x, uint32_t y) const;
	void SetChar(uint32_t x, uint32_t y, Char data);
	bool IsInside(uint32_t x, uint32_t y) const;

	void WriteString(const std::string& string, int x, int y, const Color& fg = Color(1, 1, 1, 1), const Color& bg = Color(0, 0, 0, 1));
};