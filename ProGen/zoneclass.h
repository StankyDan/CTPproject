#pragma once
#ifndef _ZONECLASS_H_
#define _ZONECLASS_H_

#include "d3dclass.h"
#include "inputclass.h"
#include "cameraclass.h"
#include "positionclass.h"
#include "terrainclass.h"


class ZoneClass
{
public:
	ZoneClass();
	ZoneClass(const ZoneClass&);
	~ZoneClass();

	bool Initialize(D3DClass*, HWND, int, int, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, float, int);

private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*);

private:

	CameraClass* m_Camera;
	PositionClass* m_Position;
	TerrainClass* m_Terrain;
	bool m_displayUI;
};

#endif