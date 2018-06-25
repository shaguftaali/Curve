#include "..\..\Includes\Maths\Matrix4.h"
#include <cassert>

  const Matrix4 Matrix4::IdentityMat = Matrix4(
	Vector4(1, 0, 0, 0),
	Vector4(0, 1, 0, 0),
	Vector4(0, 0, 1, 0),
	Vector4(0, 0, 0, 1)
);

Matrix4::Matrix4()
{
	
	setMatrixRow(0,Vector4());
	setMatrixRow(1, Vector4());
	setMatrixRow(2, Vector4());
	setMatrixRow(3, Vector4());
}

Matrix4::Matrix4(const Vector4& a_v1, const Vector4& a_v2, const Vector4& a_v3, const Vector4& a_v4)
{
	setMatrixRow(0,a_v1);
	setMatrixRow(1, a_v2);
	setMatrixRow(2, a_v3);
	setMatrixRow(3, a_v4);
}

Matrix4::Matrix4(float _arg[4][4])
{
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			mat[i][j] =_arg[i][j];
		}
	}
}

Matrix4 operator+( const Matrix4 & A,  const Matrix4 & B)
{
	Matrix4 mat4;
	for (int i=0;i<4;i++)
	{
		for (int j=0;j<4;j++)
		{
			mat4[i][j] = A[i][j] + B[i][j];
		}
	}
	return mat4;
}

Matrix4 operator-(const Matrix4 & A, const Matrix4 & B)
{
	Matrix4 mat4;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			mat4[i][j] = A[i][j] -  B[i][j];
		}
	}
	return mat4;
}

Matrix4 operator*(const Matrix4 & A, const Matrix4 & B)
{
	Matrix4 mat4;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			for (int k = 0; k<4; k++)
			{
				mat4[i][j] += A[i][k] *B[k][j];
				
			}
		}
	}
	return mat4;
}

Matrix4 operator*(float scaler, const Matrix4 & B)
{
	Matrix4 mat4;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			mat4[i][j] =scaler* B[i][j];
		}
	}
	return mat4;
}

Vector4 operator*(const Matrix4 & A, const Vector4 & B)
{
	
	Vector4 vec4;
	int index=0;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			vec4._vecArray[i] += A[i][j] * B._vecArray[j];
		}
	}
	return vec4;
}

Matrix4 operator/(float scaler, const Matrix4 & B)
{
	assert(scaler!=0);
	Matrix4 mat4;
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			mat4[i][j] = B[i][j]/scaler;
		}
	}
	return mat4;
}

float* Matrix4::operator[](int index) 
{
	assert(index>=0 && index<4);
	return mat[index];
}

const float* Matrix4::operator[](int index) const
{
	return mat[index];
}

void Matrix4::setMatrixRow(int row, const Vector4& vec4)
{
	
	
	mat[row][0]=vec4.x;
	mat[row][1] = vec4.y;
	mat[row][2] = vec4.z;
	mat[row][3] = vec4.w;
}

Matrix4 Matrix4::SetMatrix(float args[4][4])
{
	return Matrix4(args);
}

