#pragma once
#include "Plate.h"

#include <memory>

class DebugPlate
{
private:
	std::shared_ptr<Plate> _plate;
public:
	DebugPlate();
	~DebugPlate() = default;

	void Draw();
};