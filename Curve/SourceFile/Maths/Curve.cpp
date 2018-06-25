#include "..\..\Includes\Maths\Curve.h"


Curve::
Curve(vector<Vector3> a_controlPoints):
controlPoints(a_controlPoints)
{}

Vector3 Curve::GetFinalControlPoints(const vector<Vector3>& controlPoints, float t)
{
	vector<Vector3> secondOrderCP;
	for (int i=0;i<controlPoints.size()-1;i++)
	{
		secondOrderCP.push_back((controlPoints[i]* (1 - t) )+(controlPoints[i+1]*t));
	}
	if(secondOrderCP.size()>1)
	{

		return  GetFinalControlPoints(secondOrderCP,t);
	}
	else {

		return secondOrderCP[0];
	}
}

vector<float> Curve::GetFinalControlPoints(const vector<Vector3>& controlPoints, int steps)
{
	vector<Vector3> vertices;
		float t=0;
		vertices.push_back(controlPoints[0]);
		for (int i=0;i<steps;i++)
		{
			t+=1/(float)steps;
			if(t<1)
			{
				
			vertices.push_back(GetFinalControlPoints(controlPoints,t));
			}
			else
			{
				break;
			}
		}
		vertices.push_back(controlPoints[controlPoints.size()-1]);
	vector<float> verticesComponent;
		for (int i=0;i<vertices.size();i++)
		{
			verticesComponent.push_back(vertices[i].x);
			verticesComponent.push_back(vertices[i].y);
			verticesComponent.push_back(vertices[i].z);
		}
		return verticesComponent;
}


