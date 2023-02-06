#pragma once
#include "../Player.h"

#include "UIPlate.h"
#include "Plate.h"

#include <memory>

class InventoryPlate : public UIPlate
{
private:
	Player* _player;
	Vector2 _size;

public:
	InventoryPlate(Player* player);
	~InventoryPlate() = default;

	void Draw();
	void Update(float ts);
};