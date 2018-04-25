#include "agentClass.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

agentClass::agentClass(gridCreationClass* _grid, list <resourceCreationClass*>* _resources, houseCreationClass* _house)
{
	wireFrameMode = 1;

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));;
	vertices.back().setTex(XMFLOAT2(0, 1));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 10.0f, 0.0), XMFLOAT2(0, 0)));;
	vertices.back().setTex(XMFLOAT2(0.5f, 0));

	indicies.push_back(0);
	indicies.push_back(1);

	initialiseGrid(_grid);
	resources = _resources;
	house = _house;
	housePosition = XMFLOAT2(rand() % (int)gridSize.x, rand() % (int)gridSize.y);

	while (grid->heightPoint[CalculateGridPosition(housePosition)] < 1.9f)
	{
		housePosition = XMFLOAT2(rand() % (int)gridSize.x, rand() % (int)gridSize.y);
	}
}

agentClass::~agentClass()
{
}

void agentClass::initialiseGrid(gridCreationClass* _grid)
{
	grid = _grid;
	gridSize = XMFLOAT2(grid->_width, grid->_height);
}

int agentClass::agentBehaviour()
{
	origin.x = currentGridPosition.x;
	origin.z = currentGridPosition.y;

	if (!(Compare(currentGridPosition, destination)) && currentPath.size() == 0)
	{
		if (!(Compare(currentGridPosition,lastPosition)))
		{
			currentPath = agentPathfinding(destination);
			currentPathPosition = 0;
		}
		else
		{
			delayTicks++;
			if (delayTicks > 10)
			{
				currentPath = agentPathfinding(destination);
				currentPathPosition = 0;
				delayTicks = 0;
			}
		}

	}
	
	if (currentPath.size() != 0 && currentPathPosition < currentPath.size())
	{
		if (updateTicks > 5)
		{

			currentGridPosition = currentPath[currentPathPosition];
			currentPathPosition++;
			updateTicks = 0;

			if (currentPathPosition == currentPath.size())
			{
				currentPath.clear();
			}
		}
		updateTicks++;
	}
	else
	{
		if (!hasHouse)
		{
			if (hasWood)
			{
				if (CalculateDistance(currentGridPosition, housePosition) > 0.5)
				{
					destination = housePosition;
				}
				else
				{
					if (houseCost > 1)
					{
						houseCost--;
						hasWood = false;
						house->houseValue++;
						house->houseBuild();
					}
					else
					{
						houseCost--;
						house->houseValue++;
						hasWood = false;
						hasHouse = true;
					}
				}
			}
			else
			{
				if (!(Compare(foundTree,XMFLOAT2 (-1.0f, -1.0f))))
				{
					if (CalculateDistance(currentGridPosition, foundTree) > 0.5)
					{
						destination = foundTree;
					}
					else
					{						
						if (testAndChopTree(foundTree))
						{
							hasWood = true;
						}
						foundTree = XMFLOAT2(-1.0f, -1.0f);
					}
				}
				else
				{
					foundTree = findTree();
				}

			}
		}
	}

	return 0;
}

XMFLOAT2 agentClass::findTree()
{
	XMFLOAT2 closestTree = XMFLOAT2(-1.0f,-1.0f);
	float currentDistance = INT_MAX;

	for each (resourceCreationClass* resource in (*resources))
	{
		if (!(resource->cutDown))
		{
			XMFLOAT2 resourcePosition(resource->origin.x, resource->origin.z);

			if (CalculateDistance(resourcePosition, currentGridPosition) < currentDistance)
			{
				currentDistance = CalculateDistance(resourcePosition, currentGridPosition);
				closestTree = resourcePosition;
			}
		}
	}

	return closestTree;
}

bool agentClass::testAndChopTree(XMFLOAT2 _target)
{
	list <resourceCreationClass*> tempList;

	for each (resourceCreationClass* resource in (*resources))
	{
		tempList.push_back(resource);

	}

	for (int a = 0; a < (*resources).size(); a++)
	{
		XMFLOAT2 resourcePosition(tempList.back()->origin.x, tempList.back()->origin.z);

		if (Compare(resourcePosition, _target))
		{
			if (!(tempList.back()->cutDown))
			{
				tempList.back()->treeValue--;
				if (tempList.back()->treeValue <= 0)
				{
					tempList.back()->cutDown = true;
				}
				return true;
			}
			return false;
		}
		tempList.pop_back();
	}
	return false;
}

vector <XMFLOAT2> agentClass::agentPathfinding(XMFLOAT2 _target)
{
	if (_target.x < 0 || _target.x >= gridSize.x || _target.y < 0 || _target.y >= gridSize.y)
	{
		return vector <XMFLOAT2>();
	}

	if (grid->heightPoint[CalculateGridPosition(_target)] <= 1.3f)
	{
		return vector <XMFLOAT2>();
	}

	exploredPath.clear();
	toCheck.clear();
	int counter = 0;
	gridCosts.clear();
	target = _target;

	for (int a = 0; a < gridSize.x * gridSize.y; a++)
	{
		gridCosts.push_back(INT_MAX);
	}
	toCheck.push_back(currentGridPosition);
	gridCosts[CalculateGridPosition(currentGridPosition)] = CalculateDistance(currentGridPosition, target);

	while (toCheck.size() != 0 && counter<1000)
	{
		if(Compare(toCheck.back(), target))
		{ 
			return CreatePath(target, currentGridPosition);
		}
		XMFLOAT2 tempPos = toCheck.back();
		exploredPath.push_back(toCheck.back());
		toCheck.pop_back();
		FindNeighbours(tempPos, target);
		sortToCheck();
		counter++;
	}
	return vector <XMFLOAT2>();
}

bool agentClass::Compare(XMFLOAT2 a, XMFLOAT2 b)
{
	if (a.x != b.x)
	{
		return false;
	}

	if (a.y != b.y)
	{
		return false;
	}

	return true;
}

bool agentClass::CompareLists(XMFLOAT2 a, list <XMFLOAT2> b)
{
	for each (XMFLOAT2 _a in b)
	{
		if (Compare(_a, a))
		{
			return true;
		}
	}

	return false;
}


bool agentClass::CompareVector(XMFLOAT2 a, vector <XMFLOAT2> b)
{
	for each (XMFLOAT2 _a in b)
	{
		if (Compare(_a, a))
		{
			return true;
		}
	}

	return false;
}

XMFLOAT2 agentClass::FindNeighbours(XMFLOAT2 position, XMFLOAT2 target)
{
	float score = INT_MAX;
	XMFLOAT2 neighbourToReturn = XMFLOAT2 (-1,-1);


	if (position.x -1 >= 0)
	{
		XMFLOAT2 neighbour = position;
		neighbour.x -= 1;

		if (!(CompareLists(neighbour, exploredPath)))
		{
			if (!(CompareVector(neighbour, toCheck)))
			{
				if (grid->heightPoint[CalculateGridPosition(neighbour)] > 1.3f)
				{
					gridCosts[CalculateGridPosition(neighbour)] = grid->costDifference[CalculateGridPosition(neighbour)] + gridCosts[CalculateGridPosition(position)] + 1;
					toCheck.push_back(neighbour);
					if (grid->heightPoint[CalculateGridPosition(neighbour)] - grid->heightPoint[CalculateGridPosition(position)] < 0)
					{
						gridCosts[CalculateGridPosition(neighbour)] -= 1;
					}
					else
					{
						gridCosts[CalculateGridPosition(neighbour)] += 1;
					}	
				}
			}
		}
	}

	if (position.y - 1 >= 0)
	{
		XMFLOAT2 neighbour = position;
		neighbour.y -= 1;

		if (!(CompareLists(neighbour, exploredPath)))
		{
			if (!(CompareVector(neighbour, toCheck)))
			{
				if (grid->heightPoint[CalculateGridPosition(neighbour)] > 1.3f)
				{
					gridCosts[CalculateGridPosition(neighbour)] = grid->costDifference[CalculateGridPosition(neighbour)] + gridCosts[CalculateGridPosition(position)] + 1;
					toCheck.push_back(neighbour);
					if (grid->heightPoint[CalculateGridPosition(neighbour)] - grid->heightPoint[CalculateGridPosition(position)] < 0)
					{
						gridCosts[CalculateGridPosition(neighbour)] -= 1;
					}
					else
					{
						gridCosts[CalculateGridPosition(neighbour)] += 1;
					}
				}
			}
		}
	}

	if (position.x + 1 < gridSize.x)
	{
		XMFLOAT2 neighbour = position;
		neighbour.x += 1;

		if (!(CompareLists(neighbour, exploredPath)))
		{
			if (!(CompareVector(neighbour, toCheck)))
			{
				if (grid->heightPoint[CalculateGridPosition(neighbour)] > 1.3f)
				{
					gridCosts[CalculateGridPosition(neighbour)] = grid->costDifference[CalculateGridPosition(neighbour)] + gridCosts[CalculateGridPosition(position)] + 1;
					toCheck.push_back(neighbour);
					if (grid->heightPoint[CalculateGridPosition(neighbour)] - grid->heightPoint[CalculateGridPosition(position)] < 0)
					{
						gridCosts[CalculateGridPosition(neighbour)] -= 1;
					}
					else
					{
						gridCosts[CalculateGridPosition(neighbour)] += 1;
					}
				}
			}
		}
	}

	if (position.y + 1 < gridSize.y)
	{
		XMFLOAT2 neighbour = position;
		neighbour.y += 1;

		if (!(CompareLists(neighbour, exploredPath)))
		{
			if (!(CompareVector(neighbour, toCheck)))
			{
				if (grid->heightPoint[CalculateGridPosition(neighbour)] > 1.3f)
				{
					gridCosts[CalculateGridPosition(neighbour)] = grid->costDifference[CalculateGridPosition(neighbour)] + gridCosts[CalculateGridPosition(position)] + 1;
					toCheck.push_back(neighbour);
					if (grid->heightPoint[CalculateGridPosition(neighbour)] - grid->heightPoint[CalculateGridPosition(position)] < 0)
					{
						gridCosts[CalculateGridPosition(neighbour)]-= 1;
					}
					else
					{
						gridCosts[CalculateGridPosition(neighbour)]+= 1;
					}
				}
			}
		}
	}

	return neighbourToReturn;
}

vector <XMFLOAT2> agentClass::CreatePath(XMFLOAT2 position, XMFLOAT2 _target)
{
	vector <XMFLOAT2> _currentPath;
	_currentPath.push_back(position);

	while (!(Compare(_currentPath.back(),_target)))
	{
		float distanceToTarget = INT_MAX;
		float score = INT_MAX;
		XMFLOAT2 pointToAdd = XMFLOAT2(-1.0f,-1.0f);

		if (_currentPath.back().y +1 < gridSize.y)
		{
			XMFLOAT2 neighbour = _currentPath.back();
			neighbour.y += 1;
			bool noRepeat = true;

			if (_currentPath.size() > 1)
			{
				if (CompareVector(neighbour, _currentPath))
				{
					noRepeat = false;
				}
			}

			if (noRepeat)
			{
				float tempDistanceToTarget = CalculateDistance(neighbour, _target);

			/*	if(tempDistanceToTarget < distanceToTarget)*/
				{ 
					if (gridCosts[CalculateGridPosition(neighbour)] < score)
					{
						pointToAdd = neighbour;
						score = gridCosts[CalculateGridPosition(neighbour)];
						distanceToTarget = tempDistanceToTarget;
					}
				}
			}
		}

		if (_currentPath.back().y > 0)
		{
			XMFLOAT2 neighbour = _currentPath.back();
			neighbour.y -= 1;
			bool noRepeat = true;

			if (_currentPath.size() > 1)
			{
				if (CompareVector(neighbour, _currentPath))
				{
					noRepeat = false;
				}
			}

			if (noRepeat)
			{
				float tempDistanceToTarget = CalculateDistance(neighbour, _target);

				/*if (tempDistanceToTarget < distanceToTarget)*/
				{
					if (gridCosts[CalculateGridPosition(neighbour)] < score)
					{
						pointToAdd = neighbour;
						score = gridCosts[CalculateGridPosition(neighbour)];
						distanceToTarget = tempDistanceToTarget;
					}
				}
			}
		}

		if (_currentPath.back().x + 1< gridSize.x)
		{
			XMFLOAT2 neighbour = _currentPath.back();
			neighbour.x += 1;

			bool noRepeat = true;

			if (_currentPath.size() > 1)
			{
				if (CompareVector(neighbour, _currentPath))
				{
					noRepeat = false;
				}
			}

			if (noRepeat)
			{
				float tempDistanceToTarget = CalculateDistance(neighbour, _target);

				/*if (tempDistanceToTarget < distanceToTarget)*/
				{
					if (gridCosts[CalculateGridPosition(neighbour)] < score)
					{
						pointToAdd = neighbour;
						score = gridCosts[CalculateGridPosition(neighbour)];
						distanceToTarget = tempDistanceToTarget;
					}
				}
			}
		}

		if (_currentPath.back().x > 0)
		{
			XMFLOAT2 neighbour = _currentPath.back();
			neighbour.x -= 1;
			bool noRepeat = true;

			if (_currentPath.size() > 1)
			{
				if (CompareVector(neighbour, _currentPath))
				{
					noRepeat = false;
				}
			}

			if (noRepeat)
			{
				float tempDistanceToTarget = CalculateDistance(neighbour, _target);

				/*if (tempDistanceToTarget < distanceToTarget)*/
				{
					if (gridCosts[CalculateGridPosition(neighbour)] < score)
					{
						pointToAdd = neighbour;
						score = gridCosts[CalculateGridPosition(neighbour)];
						distanceToTarget = tempDistanceToTarget;
					}
				}
			}
		}
		if (pointToAdd.x != - 1)
		{
			_currentPath.push_back(pointToAdd);
		}
		else
		{
			break;
		}

	}
	vector <XMFLOAT2> reversePath;
	int currentPathSize = _currentPath.size();

	for (int a = 0; a < currentPathSize; a++)
	{
		grid->costDifference[CalculateGridPosition(_currentPath.back())] += 0.1f;
		reversePath.push_back(_currentPath.back());
		_currentPath.pop_back();
	}

	return reversePath;
}

void agentClass::sortToCheck()
{
	bool finished = false;
	float distance1;
	float distance2;

	while (!finished)
	{
		finished = true;
		if (toCheck.size() > 1)
		{
			for (int a = 0; a < toCheck.size() - 1; a++)
			{
				distance1 = CalculateDistance(toCheck[a], target);
				distance2 = CalculateDistance(toCheck[a + 1], target);
				if (distance1 < distance2)
				{
					XMFLOAT2 temp = toCheck[a];
					toCheck[a] = toCheck[a + 1];
					toCheck[a + 1] = temp;
					finished = false;
				}
			}
		}
	}
}

float agentClass::CalculateDistance(XMFLOAT2 position, XMFLOAT2 _target)
{
	XMFLOAT2 distance = position;
	distance.x -= _target.x;
	distance.y -= _target.y;
	return sqrt((distance.x * distance.x) + (distance.y * distance.y));

}

int agentClass::CalculateGridPosition(XMFLOAT2 position)
{
	return (int)((position.x * gridSize.y) + position.y);

}










//OLD PATHFINDING
//currentNode = nextNode;
//nextNode = FindNeighbours(nextNode, target);
//counter++;
//grid->costDifference[CalculateGridPosition(currentNode)] += 0.01f;


//if (CompareVector(currentNode, currentPath))
//{
//	nextNode.x = -1;
//	previousNode = currentNode;
//}

//if (nextNode.x == -1)
//{
//	if (!(Compare(currentNode, target)))
//	{
//		if (currentPath.size() != 0)
//		{
//			previousNode = currentNode;
//			nextNode = currentPath[currentPath.size() -1];
//			exploredPath.push_back(currentNode);
//			currentPath.pop_back();
//		}

//		else
//		{
//			return vector <XMFLOAT2>();
//		}
//	}

//	else
//	{
//		currentPath.push_back(currentNode);
//	}
//}

//else
//{
//	if (!(Compare(currentNode, target)))
//	{
//		currentPath.push_back(currentNode);
//		previousNode = currentNode;
//		currentNode = nextNode;
//	}
//	else
//	{
//		currentPath.push_back(currentNode);
//		nextNode = XMFLOAT2(-1.0f, -1.0f);
//	}
//}