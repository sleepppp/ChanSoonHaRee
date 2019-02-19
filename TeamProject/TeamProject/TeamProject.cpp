// TeamProject.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "TeamProject.h"

int APIENTRY WinMain(HINSTANCE instance, HINSTANCE prevInstance, LPSTR param, int command)
{
	WindowDesc desc;
	desc.AppName = L"ChanSoonHaRee";
	desc.Instance = instance;
	desc.bFullScreen = false;
	desc.bVsync = false;
	desc.Handle = NULL;
	desc.Width = WinSizeX;
	desc.Height = WinSizeY;
	desc.bToolMode = true;
	desc.command = command;

	Window::SetWindowDesc(desc);
	srand((UINT)time(0));

	Window* window = new Window();
	WPARAM wParam = window->Run();
	SafeDelete(window);

	return wParam;
}
