#pragma once
#include "IItem.h"

#include <map>
#include <vector>

class Inventory
{
private:
	float _maxWeight;
	float _currentWeight;

	std::map<ItemType, std::vector<IItem>> _items;

public:
	Inventory();
	~Inventory() = default;

	void SetMaxWeight(float w);
	float GetMaxWeight() const;

	float GetCurrentWeight() const;

	bool CanAddItem(IItem& item) const;
	void AddItem(IItem&& item);
	void RemoveItem(IItem item);

	std::map<ItemType, std::vector<IItem>> GetItems() const;
	std::vector<IItem> GetItemsOfType(ItemType type) ;
};