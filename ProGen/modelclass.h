#pragma once
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_

#include <d3d11.h>
#include "d3dclass.h"
#include <directxmath.h>
#include "textureclass.h"
#include <list>
using namespace DirectX;
using namespace std;


struct VertexType
{

	XMFLOAT3 position;
	XMFLOAT2 texture;

	VertexType() 
	{
		position = XMFLOAT3 (0,0,0);
		texture = XMFLOAT2(0,0);
	}
	
	VertexType(XMFLOAT3 pos, XMFLOAT2 tex)
	{
		position = pos;
		texture = tex;
	}

	void setTex(XMFLOAT2 tex) {
		texture = tex;
	}

	XMFLOAT3 getPos() {
		return position;
	}
};

class ModelClass
{

public:
	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, list<VertexType> verticies, list<int> indicies, XMFLOAT3 spawn);
	void Shutdown();
	void Render(ID3D11DeviceContext*, bool);
	int GetIndexCount();
	int GetVertexCount();
	unsigned long* GetIndices();
	VertexType* GetVertices();

	ID3D11ShaderResourceView* GetTexture();
	int wireFrameMode = 0;

private:
	bool InitializeBuffers(ID3D11Device* device, list<VertexType> verticies, list<int> indicies, XMFLOAT3 spawn);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*,bool);
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	XMFLOAT3 rotation = XMFLOAT3(0.0, 0.0, 0.0);
	int m_vertexCount, m_indexCount;
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();
	TextureClass* m_Texture;
	VertexType* vertices;
	unsigned long* indices;
};



#endif