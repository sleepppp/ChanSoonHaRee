#pragma once

#define CaemraMoveStartDistance 5

#define CameraMaxSpeed 30.0f 
#define CameraMinSpeed 2.0f 
#define CameraMaxDistance 960.f
#define CameraMinDistance 48.f 

#define CameraZoomMax 2.5f
#define CameraZoomMin 0.5f

class CameraManager
{
	SingletonHeader(CameraManager)
private:
	enum MoveState {FollowTarget,MoveToTarget,FreeCamera,End};
private:
	MoveState state;
	float zoomFactor;
	RECT cameraRect;
	Synthesize(Vector2,position,Position)
	Synthesize(class GameObject*,pTarget,Target)
	Synthesize(Vector2,mapSize,MapSize)
	Synthesize(float,speed,Speed)
	Vector2 saveMouse;
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