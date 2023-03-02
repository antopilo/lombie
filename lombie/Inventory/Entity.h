#pragma once
#include <NuakeRenderer/Math.h>

#include "../Core/Globals.h"
#include "../ASCII/Char.h"
#include "IItem.h"

enum class EntityType
{
	Item
};

class Entity
{
public:
	Vector2 Position;
	EntityType Type;
	Char Visual;

	Entity(){};
	virtual void Update(float ts) {};
};

class ItemEntity : public Entity
{
public:
	IItem Item;
	
	ItemEntity(const IItem& item, const Vector2& pos) 
	{
		Item = item;
		Type = EntityType::Item;
		Position = pos;

		switch (item._type)
		{
		case ItemType::Junk:
			Visual = Char('j');
			break;
		case ItemType::Valuable:
			Visual = Char('$', Globals::Colors[ColorNames::Green]);
			break;
		case ItemType::Weapon:
			Visual = Char('w', Globals::Colors[ColorNames::Blue]);
			break;
		case ItemType::Food:
			Visual = Char('f', Globals::Colors[ColorNames::DarkRed]);
			break;
		default:
			Visual = '?';
			break;
		}
	}

	~ItemEntity() = default;
};