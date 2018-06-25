#pragma once
#include "../Includes/Maths/Vector3.h"
#include "Maths/Matrix4.h"


class Camera
{
public:
	Vector3 position;
	Vector3 eyeDirection;
	Vector3 up;
	Vector3 target;
	float far;
	float near;
	float left;
	float right;
	float top;
	float bottom;
	Camera(const Vector3& a_position, const Vector3& a_target,float a_far, float a_near,float a_left, float a_right, float a_top, float a_bottom);

	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;

private:

	void SetViewMatrix();
	void SetProjectionMatrix();

};
