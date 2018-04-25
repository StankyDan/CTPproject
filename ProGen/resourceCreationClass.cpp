#include "resourceCreationClass.h"
#include <iostream>
#include <fstream>
using namespace std;

resourceCreationClass::resourceCreationClass()
{
	//const aiScene* tree = aiImportFile("../toon-pine-tree.blend", aiProcessPreset_TargetRealtime_MaxQuality);

	setUp();

}

resourceCreationClass::~resourceCreationClass()
{
}

void resourceCreationClass::setUp()
{


	// Back face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 0.0f));


	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	// Left face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	// Right face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Bottom face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Top face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Front face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 2.5, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
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

void resourceCreationClass::stumped()
{
	vertices.clear();
	indicies.clear();

	//vertices.push_back(VertexType(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT2(0, 0)));;
	//vertices.back().setTex(XMFLOAT2(0, 1));

	//vertices.push_back(VertexType(XMFLOAT3(0.0f, 0.0f + 0.5f, 0.0f), XMFLOAT2(0, 0)));;
	//vertices.back().setTex(XMFLOAT2(0.5f, 0));

	// Back face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 0.0f));


	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	// Left face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	// Right face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Bottom face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Top face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	// Front face-------------------------------------------------------------------
	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.5f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 1.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(0.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0 + 0.2, 0.0 - 0.3), XMFLOAT2(0, 0)));
	vertices.back().setTex(XMFLOAT2(1.0f, 0.0f));

	vertices.push_back(VertexType(XMFLOAT3(0.0 + 0.3, 0.0, 0.0 - 0.3), XMFLOAT2(0, 0)));
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

void resourceCreationClass::update()
{
	if (cutDown)
	{
		currentRespawn++;
		if (currentRespawn >= respawnTicks)
		{
			cutDown = false;
			hasStumped = false;
			refresh = true;
			treeValue = 3;
			indicies.clear();
			vertices.clear();
			setUp();
			currentRespawn = 0;
		}
	}



}