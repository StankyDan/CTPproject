#include "graphicsclass.h"
#include <iostream>
#include <fstream>
using namespace std;

GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_ModelGrid = 0;
	m_ColorShader = 0;
	m_TextureShader = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}

void TW_CALL CopyStdStringToClient(std::string& destinationClientString, const std::string& sourceLibraryString)
{
	destinationClientString = sourceLibraryString;
}

void TW_CALL Export(void *p)
{
	GraphicsClass* parent = static_cast<GraphicsClass*>(p);
	parent->ExportObject();
}

bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	m_Direct3D = new D3DClass;


	if (!m_Direct3D)
	{
		return false;
	}

	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)L"Could not initialize Direct3D", (LPCSTR)L"Error", MB_OK);
		return false;
	}

	TwInit(TW_DIRECT3D11, m_Direct3D->GetDevice());
	TwWindowSize(800, 600);
	TwBar *myBar;
	myBar = TwNewBar("Properties");

	TwCopyStdStringToClientFunc(CopyStdStringToClient);

	TwAddVarRW(myBar, "Biome, Left and Right keys", TW_TYPE_DIR3F, &currentBiome, " step=0.01 group=Terrain");
	TwAddVarRW(myBar, "R to remake map", TW_TYPE_DIR3F, &steepness, " step=0.01 group=Terrain");

	TwAddVarRW(myBar, "Width", TW_TYPE_FLOAT, &width, " min=0.1 max=5 step=0.01 group=Dimensions");
	TwAddVarRW(myBar, "Height", TW_TYPE_FLOAT, &height, " min=0.1 max=5 step=0.01 group=Dimensions");

	TwAddButton(myBar, "Export Object", Export, this, "group= Creation");

	m_Grid = new gridCreationClass(currentBiome, steepness, width, height);
	m_ModelGrid = new ModelClass;
	m_ModelGrid->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/stone01.tga", m_Grid->vertices, m_Grid->indicies, m_Grid->origin);
	m_Model.push_back(m_ModelGrid);

	m_TextureShader = new ColorShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}


	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, (LPCSTR)L"Could not initialize the color shader object.", (LPCSTR)L"Error", MB_OK);
		return false;
	}

	int treeCounter = 0;
	int treeSplit = 0;

	for (auto const& i : m_Grid->vertices)
	{
		if (i.position.y > 1.9f && i.position.y < 2.8f)
		{
			if (treeCounter < density)
			{
				if (treeSplit > 7)
				{
					resourceCreationClass* newTree = new resourceCreationClass();
					newTree->origin = i.position;
					newTree->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/tree.tga", newTree->vertices, newTree->indicies, newTree->origin);
					m_Model.push_back(newTree);
					m_Resource.push_back(newTree);
					treeCounter++;
					treeSplit = 0;
				}
				treeSplit++;
			}
		}
	}


	int agentCounter = 0;
	int agentSplit = 0;

	for (auto const& i : m_Grid->vertices)
	{
		if (i.position.y > 1.4f && i.position.y < 1.8f && i.position.x > 1.0f && i.position.z > 1.0f)
		{
			if (agentCounter < population)
			{
				if (agentSplit > 7)
				{
					spawnAgent(i.position);
					agentCounter++;
					agentSplit = 0;
				}
				agentSplit++;
			}
		}
	}

	



	return true;
}

void GraphicsClass::spawnAgent(XMFLOAT3 i)
{

	houseCreationClass* newHouse = new houseCreationClass();
	agentClass* newAgent = new agentClass(m_Grid, &m_Resource, newHouse);
	newAgent->origin = i;
	newAgent->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/stone01.tga", newAgent->vertices, newAgent->indicies, newAgent->origin);
	//m_Model.push_back(newAgent);
	m_Agent.push_back(newAgent);
	newAgent->currentGridPosition = XMFLOAT2((int)i.x, (int)i.z);
	newAgent->destination = XMFLOAT2((int)i.x, (int)i.z);

	XMFLOAT3 housePosition = XMFLOAT3(newAgent->housePosition.x, m_Grid->heightPoint[newAgent->CalculateGridPosition(newAgent->housePosition)], newAgent->housePosition.y);
	newHouse->setUpHouse(1.0f, -0.11f, 1.0, housePosition);
	newHouse->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/house.tga", newHouse->vertices, newHouse->indicies, newHouse->origin);
	m_Model.push_back(newHouse);
	m_House.push_back(newHouse);

}

void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}

	 //Release the model object.
	if (m_ModelGrid)
	{
		m_ModelGrid->Shutdown();
		delete m_ModelGrid;
		m_ModelGrid = 0;
	}


	for (auto const& i : m_Model)
	{
		i->Shutdown();
		delete i;
	}
		

	// Release the Direct3D object.
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	return;
}


bool GraphicsClass::Frame(CameraClass* m_Camera)
{
	bool result;

	// Render the graphics scene.
	result = Render(m_Camera);
	if (!result)
	{
		return false;
	}

	for each (agentClass* agent in m_Agent)
	{
		agent->agentBehaviour(); 
		agent->Shutdown();
		agent->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/stone01.tga", agent->vertices, agent->indicies, agent->origin);
	}

	for each (resourceCreationClass* tree in m_Resource)
	{
		tree->update();
		if (tree->cutDown && !(tree->hasStumped))
		{
			tree->stumped();
			tree->hasStumped = true;
			tree->refresh = true;
		}
		if (tree->refresh)
		{
			tree->Shutdown();
			tree->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/tree.tga", tree->vertices, tree->indicies, tree->origin);
			tree->refresh = false;
		}
	}

	for each (houseCreationClass* home in m_House)
	{
		if (home->houseValue != home->previousHouseValue)
		{
			home->Shutdown();
			home->update();
			home->houseBuild();
			home->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/house.tga", home->vertices, home->indicies, home->origin);

			if (home->houseValue >= 26)
			{
				int random = rand() % 4;

				if (random == 1)
				{
					spawnAgent(home->origin);
				}

				if (random == 2)
				{
					spawnAgent(home->origin);
				}

				if (random == 3)
				{
					spawnAgent(home->origin);
					spawnAgent(home->origin);
				}
			}
		}

	}

	return true;
}


bool GraphicsClass::Render(CameraClass* m_Camera)
{

	XMMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.1f, 0.3f, 0.9f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.


	for (auto const& i : m_Model)
	{

		i->Render(m_Direct3D->GetDeviceContext(),i->wireFrameMode);
		
		//// Render the model using the color shader.
		result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), i->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, i->GetTexture());
		if (!result)
		{
			return false;
		}

	}


	for (auto const& i : m_Agent)
	{

		i->Render(m_Direct3D->GetDeviceContext(), i->wireFrameMode);

		//// Render the model using the color shader.
		result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), i->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, i->GetTexture());
		if (!result)
		{
			return false;
		}

	}

	//m_ModelGrid->Render(m_Direct3D->GetDeviceContext(),0);

	// Render the model using the color shader.
	result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_ModelGrid->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_ModelGrid->GetTexture());
	if (!result)
	{
		return false;
	}

	TwDraw();
	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();

	return true;
}


void GraphicsClass::Randomize()
{
	delete m_Grid;
	m_Grid = new gridCreationClass(currentBiome, steepness, height, width);

	m_ModelGrid->Shutdown();
	m_ModelGrid->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../ProGen/data/stone01.tga", m_Grid->vertices, m_Grid->indicies, m_Grid->origin);

	for each (agentClass* agent in m_Agent)
	{
		agent->initialiseGrid(m_Grid);
	}


	return;
}


bool GraphicsClass::ExportObject()
{
	int offset = 1;
	ofstream object;
	ofstream texture;
	object.open("object.obj");
	texture.open("texture.mtl");

	object << "mtllib texture.mtl" << "\n";
	object << "usemtl " << "stone01.tga" << "\n";

	for each (ModelClass* _model in m_Model)
	{
		VertexType* vertices;
		unsigned long* indicies;

		m_vertexCount = _model->GetVertexCount();
		m_indexCount = _model->GetIndexCount();
		vertices = _model->GetVertices();
		indicies = _model->GetIndices();

		for (int a = 0; a < m_vertexCount; a++)
		{
			object << "v " << vertices[a].position.x << " " << vertices[a].position.y << " " << vertices[a].position.z << "\n";
		}

		for (int b = 0; b < m_vertexCount; b++)
		{
			object << "vt " << vertices[b].texture.x << " " << (1.0f - vertices[b].texture.y) << "\n";
		}

		for (int c = 0; c < m_indexCount; c += 3)
		{
			object << "f " << indicies[c] + offset << "/" << indicies[c] + offset << "/" << indicies[c] + offset << " " << indicies[c + 1] + offset << "/" << indicies[c + 1] + offset << "/" << indicies[c + 1] + offset << " " << indicies[c + 2] + offset << "/" << indicies[c + 2] + offset << "/" << indicies[c + 2] + offset << "\n";
		}

		offset += m_vertexCount;

	}


	texture << "newmtl " << "stone01.tga" << "\n";
	texture << "Ka 1.000 1.000 1.000" << "\n";
	texture << "Kd 1.000 1.000 1.000" << "\n";
	texture << "Ks 0.000 0.000 0.000" << "\n";
	texture << "d 1.0 " << "\n";
	texture << "illum 2 " << "\n";
	texture << "map_Ka ../ProGen/data/stone01.tga" << "\n";
	texture << "map_Kd ../ProGen/data/stone01.tga" << "\n";
	texture << "map_Ks ../ProGen/data/stone01.tga" << "\n";

	texture.close();
	object.close();

	return true;
}



