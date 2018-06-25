#pragma once
#include "Vector4.h"

class Matrix4
{
public:

	 Matrix4();
	 Matrix4(const Vector4& a_v1, const Vector4& a_v2, const Vector4& a_v3, const Vector4& a_v4);
	Matrix4(float _arg[4][4]);

	friend Matrix4 operator +(const Matrix4& A, const Matrix4& B);
	friend Matrix4 operator -(const Matrix4& A, const Matrix4& B);
	friend Matrix4 operator *(const Matrix4& A, const Matrix4& B);
	friend Matrix4 operator *(float scaler, const Matrix4& B);
	friend Vector4 operator *(const Matrix4& A, const Vector4& B);
	friend Matrix4 operator /(float scaler, const Matrix4& B);

	float* operator[](int index);
	const float* operator[](int index) const;

	Matrix4 SetMatrix(float args[4][4]);

	static  const Matrix4 IdentityMat;


private:
	float mat[4][4];

	void setMatrixRow(int row, const Vector4& vec4);

	
};


static  const  float identity[4][4] = {
	{ 1,0,0,0 },
{ 0,1,0,0 },
{ 0,0,1,0 },
{ 0,0,0,1 }
};