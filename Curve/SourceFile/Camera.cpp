#include "..\Includes/Camera.h"
#include <cmath>
#define PI 3.14159

Camera::Camera(const Vector3& a_position, const Vector3& a_target, float a_far, float a_near, float a_left, float a_right, float a_top, float a_bottom):
position(a_position),
target(a_target),
far(a_far),
near(a_near),
left(a_left),
right(a_right),
top(a_top),
bottom(a_bottom)

{
	eyeDirection = Vector3::Sub(a_target, a_position);
	eyeDirection = Vector3::Normalization(eyeDirection);
	SetViewMatrix();
	SetProjectionMatrix();
}


void Camera::SetViewMatrix()
{
	Vector3 xAxis = Vector3::CrossProduct(eyeDirection, Vector3(0, 1, 0));
	xAxis = Vector3::Normalization(xAxis);

	Vector3 yAxis = Vector3::CrossProduct(xAxis, eyeDirection);

	float ex = -Vector3::DotProduct(xAxis, position);
	float ey = -Vector3::DotProduct(yAxis, position);
	float ez =  Vector3::DotProduct(eyeDirection, position);

	viewMatrix = Matrix4(
		Vector4(        xAxis.x,         xAxis.y,         xAxis.z, 0),
		Vector4(        yAxis.x,         yAxis.y,         yAxis.z, 0),
		Vector4(-eyeDirection.x, -eyeDirection.y, -eyeDirection.z, 0),
		Vector4(             ex,              ey,              ez, 1)
	);

	

	
}

void Camera::SetProjectionMatrix()
{
	//const float radians = (float)FOV*(PI/180);
	float A = 2 / (right - left);
	float B = 2 / (top - bottom);
	float C=(-2)/(far-near);
	float D=-(far+near)/(far-near);
	float E = -(right + left) / (right - left);
	float F = -(top + bottom) / (top - bottom);
	projectionMatrix = Matrix4(
		Vector4(A,0,0,0),
		Vector4(0,B,0,0),
		Vector4(0,0,C,0),
		Vector4(E,F,D,1)
	);

	/*projectionMatrix = Matrix4(
		Vector4(A, 0, 0, E),
		Vector4(0, B, 0, F),
		Vector4(0, 0, C, D),
		Vector4(0, 0, 0, 1)
	);*/
}



