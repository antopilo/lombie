#pragma once
#include <NuakeRenderer/Math.h>
#include "Actions/IAction.h"

#include <queue>
#include <string>

enum class PLAYER_STATE
{
	Idle,
	Action
};

class Player
{
private:
	char icon = 'z';
	Vector2 _targetPosition;
	Vector2 _position;
	Vector2 _startPosition;

	std::string _name;
	uint32_t _age;

	float _stamina;
	float _walkSpeed;
	PLAYER_STATE _state;

	std::queue<IAction*> _actionQueue;
	float _actionEnd;
	float _timeAlive;
	float _actionStarted;

public:
	Player(const std::string& name);
	~Player() = default;

	void QueueAction(IAction* acation);

	Vector2 GetPosition() const;
	void SetPosition(uint32_t x, uint32_t y);

	void Update(float ts);
	void Draw();

	bool CanPerformAction(float cost);
	void DrainStamina(float cost);
};