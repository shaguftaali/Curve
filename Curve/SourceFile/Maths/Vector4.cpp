#include "..\..\Includes\Maths\Vector4.h"

Vector4::Vector4():
x(0),
y(0),
z(0),
w(0)
{}

Vector4::Vector4(float a_x, float a_y, float a_z, float a_w):
x(a_x),
y(a_y),
z(a_z),
w(a_w)
{
	_vecArray[0]=a_x;
	_vecArray[1] = a_y;
	_vecArray[2] = a_z;
	_vecArray[3] = 1;

}

Vector4::Vector4(Vector3 vector3, float a_w):
	x(vector3.x),
	y(vector3.y),
	z(vector3.z),
	w(a_w)
{}


