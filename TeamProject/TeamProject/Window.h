#pragma once
/*************************************************************
## WindowDesc ##
������ ���� ���õ� ���� ���� ����ü 
������.cpp���� �ʱ�ȭ ���ش�. 
*************************************************************/
struct WindowDesc
{
	wstring AppName;
	HINSTANCE Instance;
	HWND Handle;
	HDC Hdc;
	float Width;
	float Height;
	int command;
	bool bVsync;
	bool bFullScreen;
	bool bToolMode;
};
/*************************************************************
## Window ##
������â ���� �� �������� ���, ������ ���� �� �޼��� ���Ͻ� ���� �ϴ� Ŭ���� 
*************************************************************/
class Window
{
private:
	static class Program* program;		//MainGame�̶� ���� ���� 
	static WindowDesc windowDesc;		//������ ���� ���� ����ü 
public:
	static WindowDesc GetWindowDesc() { return windowDesc; }
	static void SetWindowDesc(WindowDesc desc) { windowDesc = desc; }
	static bool GetIsToolMode() { return windowDesc.bToolMode; }
public:
	Window();
	~Window();

	WPARAM Run();
	static LRESULT CALLBACK WndProc(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
private:
	void SetRegister();
	void CreateWindowApi();
	void CreateManager();
	void DeleteManager();
	void UpdateManager();
};

