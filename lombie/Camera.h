#pragma once
#include <NuakeRenderer/Math.h>

class Camera
{
private:
	

	Vector3 _position;
	Matrix4 _view;
	Matrix4 _projection;

	bool _hasChanged;
public:
	float _speed;

	Camera();
	~Camera() = default;

	void Update(float ts);
	void SetPosition(const Vector3& pos);

	Vector3 GetPosition() const;
	Matrix4 GetView();
	Matrix4 GetProjection() const;
};