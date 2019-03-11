/*************************************************************
## CameraManager ##
ī�޶� �̱��� 
*************************************************************/
#pragma once

#define CameraMoveStartDistance 30.f		

#define CameraMaxSpeed 330.0f			//ī�޶� �ִ� ���ǵ�
#define CameraMinSpeed 100.0f				//ī�޶� �ּ� ���ǵ�
#define CameraMaxDistance 300.f			
#define CameraMinDistance 30.f 

#define CameraZoomMax 2.5f				//ī�޶� �� �ִ밪
#define CameraZoomMin 0.5f				//ī�޶� �� �ּҰ�

#define CameraDefaultStrength 2.58f
#define CameraDefaultShakeTime 0.2f
/*
shakeStrength = 2.58f;
shakeTime = 0.2f;
*/

class CameraManager
{
	//�̱������� ����
	SingletonHeader(CameraManager)
private:
	enum MoveState {None,MoveToTarget,FreeCamera,End};		//ī�޶� ���� ��
private:
	MoveState state;								//ī�޶� ����
	float zoomFactor;								//ī�޶� �� 
	RECT cameraRect;								//ī�޶� ��Ʈ
	Synthesize(Vector2, position, Position)			//ī�޶� ��ǥ
	class GameObject* pTarget;						//ī�޶� ���� GameObject(����ī�޶� ���� �� ���)
	Synthesize(Vector2,mapSize,MapSize)				//��ü �� ������ (ī�޶� ������ ��)
	Synthesize(float,speed,Speed)					//ī�޶� ���ǵ� ��
	Vector2 saveMouse;								//�������� ī�޶� ���(���� ������ ���콺 ��ǥ ���� ��)

	bool isShake;
	float shakeStrength;
	float totalShakeTime;
	float shakeTime;
	float shakeDirection;
public:
	void Update();
	void OnGui();

	RECT GetRelativeRect(RECT rc);
	POINT GetRelatviePoint(POINT pt);
	Vector2 GetRelativeVector2(Vector2 v);

	Vector2 GetWorldVector2(Vector2 v);

	Vector2 GetWorldMouse();
	Vector2 GetWorldViewportCenter();
	POINT GetWorldMousePoint();
	void SetZoom(float zoom);
	float GetZoom()const { return this->zoomFactor; }
	void CameraProc(UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(class GameObject* object);
	void SetFreeCamera();

	void Shake(float strength = CameraDefaultStrength,float shakeTime = CameraDefaultShakeTime);

private:
	void UpdateRenderRect();
	void UpdateFreeCameraMode();
	void UpdateTargetCameraMode();
	void AmendCamera();
};

#define _Camera CameraManager::Get()