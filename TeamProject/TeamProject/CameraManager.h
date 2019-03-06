/*************************************************************
## CameraManager ##
카메라 싱글톤 
*************************************************************/
#pragma once

#define CameraMoveStartDistance 30.f		

#define CameraMaxSpeed 330.0f			//카메라 최대 스피드
#define CameraMinSpeed 100.0f				//카메라 최소 스피드
#define CameraMaxDistance 300.f			
#define CameraMinDistance 30.f 

#define CameraZoomMax 2.5f				//카메라 줌 최대값
#define CameraZoomMin 0.5f				//카메라 줌 최소값

class CameraManager
{
	//싱글톤으로 생성
	SingletonHeader(CameraManager)
private:
	enum MoveState {None,MoveToTarget,FreeCamera,End};		//카메라 상태 값
private:
	MoveState state;								//카메라 상태
	float zoomFactor;								//카메라 줌 
	RECT cameraRect;								//카메라 렉트
	Synthesize(Vector2, position, Position)			//카메라 좌표
	class GameObject* pTarget;						//카메라가 따라갈 GameObject(추적카메라 구현 시 사용)
	Synthesize(Vector2,mapSize,MapSize)				//전체 맵 사이즈 (카메라 보정이 들어감)
	Synthesize(float,speed,Speed)					//카메라 스피드 값
	Vector2 saveMouse;								//자유시점 카메라에 사용(이전 프레임 마우스 좌표 저장 값)
public:
	void Update();
	void OnGui();

	RECT GetRelativeRect(RECT rc);
	POINT GetRelatviePoint(POINT pt);
	Vector2 GetRelativeVector2(Vector2 v);

	Vector2 GetWorldMouse();
	Vector2 GetWorldViewportCenter();
	POINT GetWorldMousePoint();
	void SetZoom(float zoom);
	float GetZoom()const { return this->zoomFactor; }
	void CameraProc(UINT message, WPARAM wParam, LPARAM lParam);
	void SetTarget(class GameObject* object);
private:
	void UpdateRenderRect();
	void UpdateFreeCameraMode();
	void UpdateTargetCameraMode();
};

#define _Camera CameraManager::Get()