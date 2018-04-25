#pragma once
#ifndef _AGENTCLASS_H_
#define _AGENTCLASS_H_
#include "gridCreationClass.h"
#include "resourceCreationClass.h"
#include "houseCreationClass.h"

using namespace DirectX;
using namespace std;

class agentClass:public ModelClass
{

public:
	agentClass(gridCreationClass*, list <resourceCreationClass*>*, houseCreationClass*);
	~agentClass();
	int agentBehaviour();
	vector <XMFLOAT2> agentPathfinding(XMFLOAT2);
	bool Compare(XMFLOAT2 a, XMFLOAT2 b);
	bool CompareLists(XMFLOAT2, list <XMFLOAT2>);
	bool CompareVector(XMFLOAT2, vector <XMFLOAT2>);
	XMFLOAT2 FindNeighbours(XMFLOAT2 position, XMFLOAT2 target);
	vector <XMFLOAT2> CreatePath(XMFLOAT2 position, XMFLOAT2 target);
	static float CalculateDistance(XMFLOAT2 position, XMFLOAT2 target);
	int CalculateGridPosition(XMFLOAT2 position);
	void initialiseGrid(gridCreationClass*);
	void sortToCheck();
	XMFLOAT2 findTree();
	bool testAndChopTree(XMFLOAT2);

	gridCreationClass* grid;
	XMFLOAT2 gridSize;
	XMFLOAT3 origin = XMFLOAT3(0.0, 0.0, 0.0);
	XMFLOAT2 currentGridPosition = XMFLOAT2(-1.0, -1.0);
	list <VertexType> vertices;
	list<int> indicies;
	list <XMFLOAT2> exploredPath;
	vector <XMFLOAT2> currentPath;
	list <resourceCreationClass*>* resources;
	houseCreationClass* house;
	int currentPathPosition;
	XMFLOAT2 destination = XMFLOAT2(-1.0,-1.0);
	XMFLOAT2 previousNode;
	vector <float> gridCosts;
	vector <XMFLOAT2> toCheck;
	XMFLOAT2 target;
	int updateTicks;
	XMFLOAT2 housePosition;

private:
	bool hasHouse;
	bool hasWood;
	XMFLOAT2 foundTree = XMFLOAT2 (-1.0f, -1.0f);
	int houseCost = 26;
	XMFLOAT2 lastPosition;
	int delayTicks;

};



#endif
