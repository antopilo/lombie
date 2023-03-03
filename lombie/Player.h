#pragma once
#include <NuakeRenderer/Math.h>
#include "Actions/IAction.h"
#include "Inventory/Inventory.h"

#include <memory>
#include <queue>
#include <string>

class World;

enum class PLAYER_STATE
{
	Idle,
	Action
};

class Player
{
public:
	unsigned char icon = '@';

	Vector2 _targetPosition;
	Vector2 _position;
	Vector2 _startPosition;

	std::string _name;
	uint32_t _age;

	float _health;
	float _stamina;
	float _walkSpeed;
	PLAYER_STATE _state;
	World* _world;

	std::queue<std::shared_ptr<IAction>> _actionQueue;
	float _actionEnd;
	float _timeAlive;
	float _actionStarted;
	bool _justAte;
	
	Inventory _inventory;
public:
	Player(const std::string& name, World* world);
	~Player() = default;

	void QueueAction(std::shared_ptr<IAction> acation);

	Vector2 GetPosition() const;
	void SetPosition(uint32_t x, uint32_t y);

	void Update(float ts);
	void Draw();

	Inventory& GetInventory();

	bool CanPerformAction(float cost);
	void DrainStamina(float cost);
};