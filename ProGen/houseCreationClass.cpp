#include "houseCreationClass.h"
#include <iostream>
#include <fstream>
using namespace std;

houseCreationClass::houseCreationClass()
{
	setUpHouse(0.0, 0.0, 0.0, XMFLOAT3(0.0, 0.0, 0.0));
	vertices.clear();
	indicies.clear();
}

void houseCreationClass::update() 
{
	previousHouseValue = houseValue;
}

void houseCreationClass::setUpHouse(float width, float height, float depth, XMFLOAT3 _origin)
{
	_height = height;
	_width = width;
	_depth = depth;
	origin = _origin;

	// Back face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0,0.0,0.0), XMFLOAT2(0,0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 0.0f));


	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	// Left face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	// Right face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Bottom face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Top face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Front face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0 + height, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + width, 0.0, 0.0 - depth), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));


	indicies.push_back(0);
	indicies.push_back(1);
	indicies.push_back(2);
	indicies.push_back(3);
	indicies.push_back(4);
	indicies.push_back(5);
	indicies.push_back(6);
	indicies.push_back(7);
	indicies.push_back(8);
	indicies.push_back(9);
	indicies.push_back(10);
	indicies.push_back(11);
	indicies.push_back(12);
	indicies.push_back(13);
	indicies.push_back(14);
	indicies.push_back(15);
	indicies.push_back(16);
	indicies.push_back(17);
	indicies.push_back(18);
	indicies.push_back(19);
	indicies.push_back(20);
	indicies.push_back(21);
	indicies.push_back(22);
	indicies.push_back(23);
	indicies.push_back(24);
	indicies.push_back(25);
	indicies.push_back(26);
	indicies.push_back(27);
	indicies.push_back(28);
	indicies.push_back(29);
	indicies.push_back(30);
	indicies.push_back(31);
	indicies.push_back(32);
	indicies.push_back(33);
	indicies.push_back(34);
	indicies.push_back(35);

}

houseCreationClass::~houseCreationClass()
{


}

void houseCreationClass::houseBuild()
{
	vertices.clear();
	indicies.clear();

	float heightChange = rand() % 35;
	_height += heightChange / 1000;

	float widthChange = rand() % 50;
	widthChange -= 25;
	_width += widthChange / 1000;

	float depthChange = rand() % 50;
	depthChange -= 25;
	_depth += depthChange / 1000;


	setUpHouse(_width, _height, _depth, origin);

}