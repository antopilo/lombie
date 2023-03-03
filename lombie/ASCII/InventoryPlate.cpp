#include "InventoryPlate.h"
#include "PlateRenderer.h"
#include "../Core/Globals.h"
#include <iostream>
#include <format>
#include "../Core/InputManager.h"

InventoryPlate::InventoryPlate(Player* player) :
	_player(player)
{
	_size = Vector2(32, 36);

	_plate = std::make_shared<Plate>(_size.x, _size.y);
	_position.x = (16 * (1.0 / Globals::TileSize)) - _size.x / 2;
	_position.y = 0;

	const std::string title = "/ I N V /";

	float width = _size.x;
	float height = _size.y;
	Char corner = Char(176);
	_plate->SetChar(0, 0, 192);
	_plate->SetChar(_size.x - 1, 0, 217);
	_plate->SetChar(0, _size.y - 1, 218);
	_plate->SetChar(_size.x - 1, _size.y - 1, 191);

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

	// Create zones
	_zones.emplace("weapon_header", Zone(2, 12, 34, 34));
}

void InventoryPlate::Draw()
{
	Inventory& inv = _player->GetInventory();

	int line = _plate->GetHeight() - 2;
	// Junk
	auto junk = inv.GetItemsOfType(ItemType::Junk);
	if (junk.size() > 0)
	{

	}

	auto weapons = inv.GetItemsOfType(ItemType::Weapon);
	if (weapons.size() > 0)
	{
		// Update zone
		Zone& zone = _zones["weapon_header"];
		zone.y = line;
		zone.yy = line;

		Color bg = Color(0, 0, 0, 1);
		const Color hoverColor = Color(0.2, 0.2, 0.2, 1.0);

		if (zone._state == ZoneState::Hover)
		{
			bg = hoverColor;
		}
		_plate->WriteString("W e a p o n", 2, line, Color(1, 1, 1, 1), bg);

		line--;

		for (const auto& w : weapons)
		{
			int nameLength = w._name.size() + 1;
			
			_plate->SetChar(3, line, Char(254, Color(0.5, 0.5, 0, 1.0)));
			_plate->SetChar(4, line, Char(' ', Color(0.5, 0.5, 0, 1.0)));

			_plate->WriteString(w._name + " ", 5, line, Color(0.5, 0, 0, 1));

			std::string weightLabel = std::format("{}", w._weight) + "lb";
			_plate->WriteString(weightLabel, 5 + nameLength, line, Color(0.2, 0.2, 0.2, 1.0));
			line--;
		}
	}

	// Food
	auto food = inv.GetItemsOfType(ItemType::Food);
	if (food.size() > 0)
	{
		// Update zone
		Zone& zone = _zones["food_header"];
		zone.y = line;
		zone.yy = line;

		Color bg = Color(0, 0, 0, 1);
		const Color hoverColor = Color(0.2, 0.2, 0.2, 1.0);

		if (zone._state == ZoneState::Hover)
		{
			bg = hoverColor;
		}
		_plate->WriteString("F o o d", 2, line, Color(1, 1, 1, 1), bg);

		line--;

		for (const auto& f : food)
		{
			int nameLength = f._name.size() + 1;
			
			_plate->SetChar(3, line, Char(254, Color(0.5, 0.5, 0, 1.0)));
			_plate->SetChar(4, line, Char(' ', Color(0.5, 0.5, 0, 1.0)));

			_plate->WriteString(f._name + " ", 5, line, Color(0.5, 0, 0, 1));

			// Reset weight if previous name was longer
			_plate->WriteString("          ", 5 + nameLength, line, Color(0.2, 0.2, 0.2, 1.0));

			std::string weightLabel = std::format("{}", f._weight) + "lb";
			_plate->WriteString(weightLabel, 5 + nameLength, line, Color(0.2, 0.2, 0.2, 1.0));
			line--;
		}
	}

	// Delete Food visually from Inventory
	if(_player->_justAte)
	{
		// Delete category then delete the last item from UI
		if(food.size() == 0)
		{
			_plate->WriteString("            ", 2, line, Color(1, 1, 1, 1));
			line--;
		}
		
		_player->_justAte = false;
				
		_plate->SetChar(3, line, Char(' ', Color(0.5, 0.5, 0, 1.0)));
		_plate->SetChar(4, line, Char(' ', Color(0.5, 0.5, 0, 1.0)));
		_plate->WriteString("            ", 5, line, Color(0.5, 0, 0, 1));
	}

	Matrix4 transform = Matrix4(1);
	transform = glm::scale(transform, Vector3(Globals::TileSize));
	transform = glm::translate(transform, Vector3(_position.x, _position.y, 0.1f));

	PlateRenderer::Get().RenderPlateHalf(*_plate.get(), transform, Matrix4(1), glm::ortho(0.0, 16.0, 0.0, 9.0, -1.0, 1.0));
}

void InventoryPlate::Update(float ts)
{

}