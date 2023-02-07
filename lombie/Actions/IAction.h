#pragma once

class IAction
{
public:
	IAction() = default;
	virtual void Execute() {};
};