#include "EatAction.h"

#include <iostream>

#include "../Player.h"
#include "../Inventory/Entity.h"

EatAction::EatAction(Player* player)
{
    _player = player;
}

void EatAction::Execute()
{
    if (_player->_inventory.GetItemsOfType(ItemType::Food).size() > 0)
    {
        IItem firstItem = _player->_inventory.GetItemsOfType(ItemType::Food)[0];
        _player->_inventory.RemoveItem(firstItem);
        _player->justAte = true;
    }
    else
    {
        std::cout << "Nothing to eat!!" << std::endl;
    }
}