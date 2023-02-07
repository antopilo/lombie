#include "Inventory.h"

#include <algorithm>

Inventory::Inventory()
{
	_maxWeight = 20.0f;
	_currentWeight = 0.0f;
}

float Inventory::GetMaxWeight() const
{
	return _maxWeight;
}

void Inventory::SetMaxWeight(float w)
{
	_maxWeight = w;
}

float Inventory::GetCurrentWeight() const
{
	return _currentWeight;
}

bool Inventory::CanAddItem(IItem& item) const
{
	float potentialWeight = _currentWeight + item._weight;
	return potentialWeight < _maxWeight;
}

void Inventory::AddItem(IItem&& item)
{
	if (!CanAddItem(item))
	{
		return;
	}

	_currentWeight += item._weight;
	_items[item._type].push_back(std::move(item));
}

void Inventory::RemoveItem(IItem item)
{
	if (_items.find(item._type) == _items.end())
	{
		return;
	}

	std::vector<IItem>& container = _items[item._type];

	int idx = 0;
	for (const auto& i : container)
	{
		if (i._name == item._name)
		{
			break;
		}

		idx++;
	}

	container.erase(container.begin() + idx);
}

std::map<ItemType, std::vector<IItem>> Inventory::GetItems() const
{
	return _items;
}

std::vector<IItem> Inventory::GetItemsOfType(ItemType type)
{
	return _items[type];
}
