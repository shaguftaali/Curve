#pragma once
#include <vector>
#include "Vector3.h"

using namespace std;

class  Curve
{
public:
	Curve(vector<Vector3> a_controlPoints);
	Vector3 GetFinalControlPoints(const vector<Vector3>& controlPoints, float t);
	vector<float> GetFinalControlPoints(const vector<Vector3>& controlPoints, int steps);
private:
	vector<Vector3> controlPoints;
};