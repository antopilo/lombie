#pragma once
#include "IAction.h"

class Player;
class ItemEntity;

class EatAction: public IAction
{
private:
    Player* _player = nullptr;

public:
    EatAction(Player* player);

    void Execute() override;
    
};
