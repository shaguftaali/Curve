#pragma once
#include "Vector3.h"
//#include "Matrix4.h"

class Vector4
{
public:
	float x;
	float y;
	float z;
	float w;

	Vector4();

	Vector4(float a_x,float a_y,float a_z,float a_w);

	Vector4(Vector3 vector3, float a_w);

	float _vecArray[4];

	
};
