#pragma once
#ifndef _GRIDCREATIONCLASS_H_
#define _GRIDCREATIONCLASS_H_

#include <d3d11.h>
#include <directxmath.h>
#include <list>
#include <vector>
#include "modelclass.h"
#include "PerlinNoise.h"

using namespace DirectX;
using namespace std;

class gridCreationClass
{
public:
	vector <float> heightPoint;
	list <VertexType> vertices;
	list<int> indicies;
	XMFLOAT3 origin = XMFLOAT3(0.0, 0.0, 0.0);

	float setValues(float);
	gridCreationClass(float, float, float, float);
	~gridCreationClass();
	float _width;
	float _height;
	vector <float> costDifference;
private:




};

#endif