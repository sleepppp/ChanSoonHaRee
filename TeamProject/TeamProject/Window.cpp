#include "stdafx.h"
#include "Window.h"

#include "Program.h"

WindowDesc Window::windowDesc;
Program* Window::program = nullptr;

Window::Window()
{
	this->SetRegister();
	this->CreateWindowApi();
}


Window::~Window()
{
	if (windowDesc.bFullScreen == true)
		ChangeDisplaySettings(NULL, 0);

	DestroyWindow(windowDesc.Handle);

	UnregisterClass(windowDesc.AppName.c_str(), windowDesc.Instance);
}

WPARAM Window::Run()
{
	MSG msg = { 0 };

	//=========Init Manager=================================
	this->CreateManager();
	//=======================================================
	if (Window::windowDesc.bToolMode == true)
	{
		Window::program = new Program();
	}
	else
	{

	}
	Window::program->Init();
	//============Main Loop===================================
	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				break;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{

			//Rendering
			Window::program->Render();
		}
	}
	//=======================================================
	Window::program->Release();
	SafeDelete(Window::program);
	//================Release Manager===============================
	this->DeleteManager();
	//==============================================================

	return msg.wParam;
}

LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			PostMessage(handle, WM_DESTROY, 0, 0);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}


	return (DefWindowProc(handle, message, wParam, lParam));
}

void Window::SetRegister()
{
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										//클래스 여분 메모리 설정
	wndClass.cbWndExtra = 0;										//윈도우 여분 메모리 설정
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//윈도우 백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//윈도우 커서 모양
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//윈도우 아이콘 모양
	wndClass.hInstance = windowDesc.Instance;						//윈도우 인스턴스 번호
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//윈도우 프로시져
	wndClass.lpszClassName = windowDesc.AppName.c_str();			//윈도우 클래스 이름
	wndClass.lpszMenuName = NULL;									//윈도우 메뉴 이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//윈도우 창 스타일

																	//윈도우 정보를 등록해준다
	RegisterClass(&wndClass);

	if (windowDesc.bFullScreen == true)
	{
		DEVMODE devMode = { 0 };
		devMode.dmSize = sizeof(DEVMODE);
		devMode.dmPelsWidth = (DWORD)windowDesc.Width;
		devMode.dmPelsHeight = (DWORD)windowDesc.Height;
		devMode.dmBitsPerPel = 32;
		devMode.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		ChangeDisplaySettings(&devMode, CDS_FULLSCREEN);
	}


}

void Window::CreateWindowApi()
{
	RECT rect = { 0, 0, (LONG)windowDesc.Width, (LONG)windowDesc.Height };

	UINT centerX = (GetSystemMetrics(SM_CXSCREEN) - (UINT)windowDesc.Width) / 2;
	UINT centerY = (GetSystemMetrics(SM_CYSCREEN) - (UINT)windowDesc.Height) / 2;

	windowDesc.Handle = CreateWindow(
		windowDesc.AppName.c_str(),
		windowDesc.AppName.c_str(),
		WS_OVERLAPPEDWINDOW,
		centerX - WinSizeX / 2,
		centerY - WinSizeY / 2,
		WinSizeX,
		WinSizeY,
		NULL,
		(HMENU)NULL,
		windowDesc.Instance,
		NULL);

	assert(windowDesc.Handle != NULL);

	windowDesc.Hdc = GetDC(windowDesc.Handle);

	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	SetWindowPos(windowDesc.Handle, NULL, centerX - WinSizeX / 2, centerY - WinSizeY / 2, WinSizeX, WinSizeY
		, SWP_NOZORDER | SWP_NOMOVE);

	MoveWindow
	(
		windowDesc.Handle
		, centerX, centerY
		, rect.right - rect.left, rect.bottom - rect.top
		, TRUE
	);

	ShowWindow(windowDesc.Handle, Window::windowDesc.command);
	//SetForegroundWindow(windowDesc.Handle);
	//SetFocus(windowDesc.Handle);

	ShowCursor(true);
}

void Window::CreateManager()
{

}

void Window::DeleteManager()
{

}
