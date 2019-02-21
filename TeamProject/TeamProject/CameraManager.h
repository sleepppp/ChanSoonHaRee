/*************************************************************
## CameraManager ##
ī�޶� �̱��� 
*************************************************************/
#pragma once

#define CaemraMoveStartDistance 5		

#define CameraMaxSpeed 30.0f			//ī�޶� �ִ� ���ǵ�
#define CameraMinSpeed 2.0f				//ī�޶� �ּ� ���ǵ�
#define CameraMaxDistance 960.f			
#define CameraMinDistance 48.f 

#define CameraZoomMax 2.5f				//ī�޶� �� �ִ밪
#define CameraZoomMin 0.5f				//ī�޶� �� �ּҰ�

class CameraManager
{
	//�̱������� ����
	SingletonHeader(CameraManager)
private:
	enum MoveState {FollowTarget,MoveToTarget,FreeCamera,End};		//ī�޶� ���� ��
private:
	MoveState state;								//ī�޶� ����
	float zoomFactor;								//ī�޶� �� 
	RECT cameraRect;								//ī�޶� ��Ʈ
	Synthesize(Vector2,position,Position)			//ī�޶� ��ǥ
	Synthesize(class GameObject*,pTarget,Target)	//ī�޶� ���� GameObject(����ī�޶� ���� �� ���)
	Synthesize(Vector2,mapSize,MapSize)				//��ü �� ������ (ī�޶� ������ ��)
	Synthesize(float,speed,Speed)					//ī�޶� ���ǵ� ��
	Vector2 saveMouse;								//�������� ī�޶� ���(���� ������ ���콺 ��ǥ ���� ��)
public:
	void Update();
	void OnGui();

	RECT GetRelativeRect(RECT rc);
	POINT GetRelatviePoint(POINT pt);
	Vector2 GetReltativeVector2(Vector2 v);
	Vector2 GetWorldMouse();
	Vector2 GetWorldViewportCenter();
	POINT GetWorldMousePoint();
	void SetZoom(float zoom);
	float GetZoom()const { return this->zoomFactor; }
	void CameraProc(UINT message, WPARAM wParam, LPARAM lParam);
private:
	void UpdateRenderRect();
	void UpdateFreeCameraMode();
};

#define _Camera CameraManager::Get()