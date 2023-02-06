#pragma once
#include "Plate.h"

#include <functional>
#include <map>
#include <memory>

enum class ZoneState
{
	Idle,
	Hover,
	Click
};

class Zone
{
public:
	ZoneState _state;

	int x;
	int y;
	int xx;
	int yy;
	Zone() = default;
	Zone(int startX, int startY, int endX, int endY);
	~Zone() = default;

	bool IsInside(int x, int y);
	std::function<void()> _callback;
};

class UIPlate
{
protected:
	std::shared_ptr<Plate> _plate;
	Vector2 _position;

	std::map<std::string, Zone> _zones;

public:
	UIPlate() = default;
	UIPlate(const Vector2& position, uint32_t width, uint32_t height);

	virtual void Draw();

	void Hover(int mx, int my);
	bool AcceptInput(float mouseX, float mouseY);
	std::shared_ptr<Plate> GetPlate();
	Vector2 GetPosition() const;
};