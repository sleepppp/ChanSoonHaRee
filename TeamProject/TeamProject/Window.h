#pragma once
//윈메인 정보를 담고 있는 구조체 
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

class Window
{
private:
	static class Program* program;
	static WindowDesc windowDesc;
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

