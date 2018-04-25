#pragma once
#ifndef _RESOURCECREATIONCLASS_H_
#define _RESOURCECREATIONCLASS_H_
#include "modelclass.h"
//#include <assimp/cimport.h>
//#include <assimp/postprocess.h>
//#include <assimp/scene.h>

using namespace DirectX;
using namespace std;

class resourceCreationClass: public ModelClass
{

public:
	resourceCreationClass();
	~resourceCreationClass();
	void setUp();
	void stumped();
	void update();
	XMFLOAT3 origin = XMFLOAT3(0.0, 0.0, 0.0);

	list <VertexType> vertices;
	list<int> indicies;
	int treeValue = 3;
	bool cutDown = false;
	bool hasStumped = false;
	bool refresh = false;
	int respawnTicks = 2000;
	int currentRespawn = 0;
private:



};








#endif