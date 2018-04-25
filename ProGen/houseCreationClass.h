#pragma once
#ifndef _HOUSECREATIONCLASS_H_
#define _HOUSECREATIONCLASS_H_
#include "modelclass.h"
//#include <assimp/cimport.h>
//#include <assimp/postprocess.h>
//#include <assimp/scene.h>

using namespace DirectX;
using namespace std;

class houseCreationClass : public ModelClass
{
public:
	void setUpHouse(float, float, float, XMFLOAT3);
	houseCreationClass();
	~houseCreationClass();
	void houseBuild();
	void update();

	XMFLOAT3 origin = XMFLOAT3(0.0, 0.0, 0.0);
	list <VertexType> vertices;
	list<int> indicies;
	int previousHouseValue = 0;

	float _height;
	float _width;
	float _depth;
	int houseValue = 0;
	bool houseCompleted;


};
#endif
