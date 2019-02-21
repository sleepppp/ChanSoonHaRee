#include "stdafx.h"
#include "Window.h"

#include "Program.h"
//static ������ ���������� �Ʒ��� ���� �ݵ�� cpp���� �ʱ�ȭ ���־�� �Ѵ�. ������ ���۸� �غ�����
WindowDesc Window::windowDesc;
Program* Window::program = nullptr;

/*********************************************************************************
## WIndow ## 
������ Ŭ���� ������ 
�������� ��� �� ������ â ����
**********************************************************************************/
Window::Window()
{
	this->SetRegister();
	this->CreateWindowApi();
}
/*********************************************************************************
## ~Window ##
������ Ŭ���� �Ҹ���
**********************************************************************************/
Window::~Window()
{
	//���÷��� ���� �ʱ�ȭ 
	if (windowDesc.bFullScreen == true)
		ChangeDisplaySettings(NULL, 0);
	//������ ����
	DestroyWindow(windowDesc.Handle);
	//�������� ���� 
	UnregisterClass(windowDesc.AppName.c_str(), windowDesc.Instance);
}
/*********************************************************************************
## Run ##
�������� ���� ����
**********************************************************************************/
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
			this->UpdateManager();
			Window::program->Update();
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

/*********************************************************************************
## WndProc ##
���� ���Ͻ� 
**********************************************************************************/
LRESULT Window::WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (ImGui::WndProc((UINT*)handle, message, wParam, lParam)) return true;
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
	if (message == WM_KEYDOWN || message == WM_MOUSEMOVE)
		Input::Get()->InputProc(message, wParam, lParam);
	if (message == WM_MOUSEWHEEL)
		CameraManager::Get()->CameraProc(message, wParam, lParam);

	return (DefWindowProc(handle, message, wParam, lParam));
}
/*********************************************************************************
## SetRegister ##
�������� ���
**********************************************************************************/
void Window::SetRegister()
{
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;										//Ŭ���� ���� �޸� ����
	wndClass.cbWndExtra = 0;										//������ ���� �޸� ����
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);	//������ ��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);					//������ Ŀ�� ���
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);				//������ ������ ���
	wndClass.hInstance = windowDesc.Instance;						//������ �ν��Ͻ� ��ȣ
	wndClass.lpfnWndProc = (WNDPROC)WndProc;						//������ ���ν���
	wndClass.lpszClassName = windowDesc.AppName.c_str();			//������ Ŭ���� �̸�
	wndClass.lpszMenuName = NULL;									//������ �޴� �̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;						//������ â ��Ÿ��

																	//������ ������ ������ش�
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
/*********************************************************************************
## CreateWindowApi ##
������ ���� �� ���
**********************************************************************************/
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
/*********************************************************************************
## CreateManager ##
�̱��� �޴����� ���� �κ�
**********************************************************************************/
void Window::CreateManager()
{
	DXRenderer::Create();
	ImGui::Create(Window::GetWindowDesc().Handle, _D3DDevice, _D3DDeviceContext);
	{
		ImGui::StyleColorsClassic();
	}
	Input::Create();
	CameraManager::Create();
	Time::Create();
	ImageManager::Create();
	ObjectManager::Create();
}
/*********************************************************************************
## DeleteManager ##
�̱��� �޴����� ���� �κ�
**********************************************************************************/
void Window::DeleteManager()
{
	ObjectManager::Delete();
	ImageManager::Delete();
	Time::Delete();
	CameraManager::Delete();
	Input::Delete();
	ImGui::Delete();
	DXRenderer::Delete();
}

/**********************************************************************************
## UpdateManager ##
�޴����� ������Ʈ 
***********************************************************************************/
void Window::UpdateManager()
{
	Time::Get()->Update();
	Input::Get()->Update();
	CameraManager::Get()->Update();
	ImGui::Update();
}
