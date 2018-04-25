#include <windows.h>
#include "inputclass.h"
#include "graphicsclass.h"
#include "cameraclass.h"

#pragma once
#ifndef _SYSTEMCLASS_H_
#define _SYSTEMCLASS_H_
#define WIN32_LEAN_AND_MEAN



class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool Initialize();
	void Shutdown();
	void Run();

	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);
	CameraClass* m_Camera;

private:
	bool Frame();
	void InitializeWindows(int&, int&);
	void ShutdownWindows();
	float x, y, z;
	int counter = 0;
private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;


};


static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
static SystemClass* ApplicationHandle = 0;

#endif