#include "stdafx.h"
#include "Input.h"

SingletonCpp(Input)

/*********************************************************************
## Input ##
**********************************************************************/
Input::Input()
{
	//ó���� ��� Ű�� �������� ���� ���·� �ʱ�ȭ
	keyCurrent.reset();
	keyPast.reset();

	mousePosition.x = mousePosition.y = 0;
}
/*********************************************************************
## ~Input ## 
**********************************************************************/
Input::~Input() {}

/*********************************************************************
## Update ## 
����Ű�� ����Ű�� ���� 
**********************************************************************/
void Input::Update()    
{
	keyPast = keyCurrent;	
}
/*********************************************************************
## GetKeyDown ## 
�ѹ� ������ �� 
@@ int key : Ű 

@@ return bool : keyDown���� 
**********************************************************************/
bool Input::GetKeyDown(int key)
{
	//�ش� Ű�� ���� ����
	if (GetAsyncKeyState(key) & 0x8000)
	{
		//�� Ű�� �������� �ʾҴٸ�
		if (!keyPast[key])
		{
			//����Ű�� ���� ���·� �ٲٰ� return true
			keyCurrent.set(key, true);
			return true;
		}
	}
	//�ش� Ű�� ������ ���� ����
	else keyCurrent.set(key, false);   //����Ű�� ������ ���� ���·� �ٲ�

	return false;
}

/*********************************************************************
## GetKeyUp ## 
���� Ű���� ���� ��
@@ int key : Ű

@@ return bool : keyUp���� 
**********************************************************************/
bool Input::GetKeyUp(int key)
{
	//�ش� Ű�� ���� ����					����Ű�� ���� ���·� �ٲ�
	if (GetAsyncKeyState(key) & 0x8000) keyCurrent.set(key, true);
	//�ش� Ű�� ������ ���� ����
	else
	{
		//�� Ű�� �����־��ٸ�
		if (keyPast[key])
		{
			//����Ű�� ������ ���� ���·� �ٲٰ� return true
			keyCurrent.set(key, false);
			return true;
		}
	}

	return false;
}

/*********************************************************************
## Getkey ##
�ش� Ű�� ���� �ִ��� 
@@ int key : Ű 

@@ return bool : StayKey���� 
**********************************************************************/
bool Input::GetKey(int key)
{
	if (GetAsyncKeyState(key) & 0x8000) return true;

	return false;
}

/*********************************************************************
## IsToggleKey ## 
@@ int key : Ű

@@ return bool : ��ۿ��� 
**********************************************************************/
bool Input::IsToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001) return true;

	return false;
}
/*********************************************************************
## InputProc ## 
@@ UINT message : ���Ͻ� �޼��� 
@@ WPARAM wparam : Ű �Է� ���� �޼���
@@ LPARAM lParam : ���콺 ���� �޼��� 
**********************************************************************/
LRESULT Input::InputProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_MOUSEMOVE)
	{
		mousePosition.x = static_cast<float>LOWORD(lParam);
		mousePosition.y = static_cast<float>HIWORD(lParam);
	}

	return TRUE;
}

/*********************************************************************
## GetMousePositionPoint ## 
���콺 ��ǥ PONT ������ ��ȯ

@@ return POINT : ���콺��ǥ ����Ʈ ��ȯ
**********************************************************************/

 POINT Input::GetMousePositionPoint()
{
	POINT p;
	p.x = (LONG)mousePosition.x;
	p.y = (LONG)mousePosition.y;
	return p;
}
