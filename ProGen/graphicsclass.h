#pragma once
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_

#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "gridCreationClass.h"
#include "resourceCreationClass.h"
#include "agentClass.h"
#include "colorshaderclass.h"
#include <AntTweakBar.h>
#include "houseCreationClass.h"


const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();
	bool ExportObject();
	void spawnAgent(XMFLOAT3);


	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(CameraClass* m_Camera);
	void Randomize();
	float currentBiome = 4.3f;
	float steepness = 0.0f;
	float width = 40.0f;
	float height = 40.0f;
	XMFLOAT2 position;

private:
	bool Render(CameraClass* m_Camera);
	list <ModelClass*> m_Model;
	list <agentClass*> m_Agent;
	list <houseCreationClass*> m_House;
	list <resourceCreationClass*> m_Resource;
	ModelClass* m_ModelGrid;
	gridCreationClass* m_Grid;
	ColorShaderClass* m_ColorShader;
	ColorShaderClass* m_TextureShader;
	int density = 350;
	int population = 4;
	int m_indexCount, m_vertexCount;


private:
	D3DClass* m_Direct3D;
};

#endif