#pragma once
#include <string>

enum class ItemType
{
	Food,
	Weapon,
	Junk,
	Meds,
	Valuable
};

class IItem
{
public:
	std::string _name;
	float _weight;
	ItemType _type;

	IItem() = default;
	IItem(const std::string& name, float weight, ItemType type) :
		_name(name),
		_weight(weight),
		_type(type)
	{
	}
};