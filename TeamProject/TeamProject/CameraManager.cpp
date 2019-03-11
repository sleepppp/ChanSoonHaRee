#include "stdafx.h"
#include "CameraManager.h"

#include "GameObject.h"

SingletonCpp(CameraManager)

/***************************************************************************
## CameraManager ## 
***************************************************************************/
CameraManager::CameraManager()
	:mapSize((float)WinSizeX,(float)WinSizeY),pTarget(nullptr),zoomFactor(1.0f),
	speed(100.0f), state(CameraManager::FreeCamera), shakeDirection(1.f), moveStartDistance(CameraMoveStartDistance)
{
	this->position = Vector2(0.f,0.f);
	this->cameraRect = Figure::RectMake(
		(int)this->position.x,(int)this->position.y, WinSizeX, WinSizeY);
	this->saveMouse = _Input->GetMousePosition();
}

/***************************************************************************
## ~CameraManager ##
***************************************************************************/
CameraManager::~CameraManager()
{

}

/***************************************************************************
## Update ## 
ī�޶� ���¿� ���� Update
***************************************************************************/
void CameraManager::Update()
{
	//TODO Ÿ�� ī�޶��ϰ� ī�޶� ���� �߰�
	switch (state)
	{
	case CameraManager::None:
	case CameraManager::MoveToTarget:
		this->UpdateTargetCameraMode();
		break;
	case CameraManager::FreeCamera:
		this->UpdateFreeCameraMode();
		break;
	case CameraManager::End:
		if (isShake == true)
		{
			shakeDirection = -1.f * shakeDirection;
			shakeTime -= _TimeManager->DeltaTime();
			shakeStrength -= (shakeTime / totalShakeTime) *_TimeManager->DeltaTime();
			float strengh = shakeStrength * shakeDirection;
			position += Vector2(0.f, strengh);
			this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));

			if (shakeTime <= 0.f)
			{
				isShake = false;
			}
			this->AmendCamera();
		}
		break;
	default:
		break;
	}
}


/***************************************************************************
## OnGui ## 
***************************************************************************/
void CameraManager::OnGui()
{
	static float strength = CameraDefaultStrength;
	static float time = CameraDefaultShakeTime;
	ImGui::Begin("Camera");
	{
		ImGui::SliderFloat("Strength", &strength, 0.5f, 10.f);
		ImGui::SliderFloat("ShakeTime", &time, 0.1f, 2.f);
		if (ImGui::Button("Shake"))
			_Camera->Shake(strength, time);
	}
	ImGui::End();
}
/***************************************************************************
## GetRelaticeRect ## 
ī�޶� �����ǥ�� RECT ����
@@ RECT rc : ī�޶� ���� ���� ��Ʈ 

@@ return RECT : ī�޶� ������ ��Ʈ ��ȯ 
***************************************************************************/
RECT CameraManager::GetRelativeRect(RECT rc)
{
	Figure::MoveRect(&rc, (int)-position.x, (int)-position.y);
	rc.left =(LONG)(CastingFloat(rc.left) * zoomFactor);
	rc.top = (LONG)(CastingFloat(rc.top) * zoomFactor);
	rc.right = (LONG)(CastingFloat(rc.right) * zoomFactor);
	rc.bottom =(LONG)( CastingFloat(rc.bottom) * zoomFactor);
	return std::move(rc);
}
/***************************************************************************
## GetRelativePoint ## 
ī�޶� �����ǥ�� POINT ���� �� ��ȯ 
@@ POINT pt : ���� ���� POINT

@@ return POINT : ���� �� POINT ��ȯ 
***************************************************************************/
POINT CameraManager::GetRelatviePoint(POINT pt)
{
	pt.x -= (LONG)position.x;
	pt.y -= (LONG)position.y;
	pt.x = (LONG)(CastingFloat(pt.x) * zoomFactor);
	pt.y = (LONG)(CastingFloat(pt.y) * zoomFactor);
	return std::move(pt);
}

/***************************************************************************
## GetRelativeVector2 ## 
ī�޶� �����ǥ�� Vector2 ���� �� ��ȯ
@@ Vector2 v : ���� ���� Vector2 

@@ return Vector2 : ���� �� Vector2��ȯ 
***************************************************************************/
Vector2 CameraManager::GetRelativeVector2(Vector2 v)
{
	v.x -= position.x;
	v.y -= position.y;
	v = v * zoomFactor;
	return std::move(v);
}
Vector2 CameraManager::GetWorldVector2(Vector2 v)
{
	return Vector2(v.x / zoomFactor + position.x,v.y / zoomFactor + position.y);
}
/***************************************************************************
## GetWorldMouse ## 
ī�޶� ���� ���� ���콺��ǥ ��ȯ

@@ return Vector2 : ���� ������ ���콺��ǥ 
***************************************************************************/
Vector2 CameraManager::GetWorldMouse()
{
	Vector2 mouse = _Input->GetMousePosition();
	return  Vector2(mouse.x / zoomFactor + position.x, mouse.y / zoomFactor + position.y);
}
/***************************************************************************
## GetWorldViewportCenter ## 

@@ return Vector2 : ���� �������� ȭ�� �߽� ��ȯ
***************************************************************************/
Vector2 CameraManager::GetWorldViewportCenter()
{
	return Vector2((position.x + (float)(WinSizeX / 2) / zoomFactor) , (position.y + (float)(WinSizeY / 2) / zoomFactor) );
}

/***************************************************************************
## GetWorldMosuePoint ## 

@@ return POINT : ���� �������� ���콺 ��ǥ POINT ��ȯ 
***************************************************************************/
POINT CameraManager::GetWorldMousePoint()
{
	Vector2 mouse = _Input->GetMousePosition();
	mouse = Vector2(mouse.x / zoomFactor + position.x, mouse.y / zoomFactor + position.y);
	return { (LONG)mouse.x,(LONG)mouse.y };
}
/***************************************************************************
## SetZoom ## 
@@ float Zoom : �� ��ġ 
***************************************************************************/
void CameraManager::SetZoom(float zoom)
{
	this->zoomFactor = Math::Clampf(zoom, CameraZoomMin, CameraZoomMax);
}
/***************************************************************************
## UpdateRenderRect ## 
ȭ�� Rect��ȯ
***************************************************************************/
void CameraManager::UpdateRenderRect()
{
	this->cameraRect = Figure::RectMake(
		(int)this->position.x, (int)this->position.y, WinSizeX, WinSizeY);
}
/***************************************************************************
## UpdateFreeCameraMode ## 
FreeCaemra ������ ���� ������Ʈ 
***************************************************************************/
void CameraManager::UpdateFreeCameraMode()
{
	if (IsMouseOnGui == false)
	{
		Vector2 currentMouse = _Input->GetMousePosition();
		if (_Input->GetKey(VK_RBUTTON))
		{
			if (this->saveMouse != currentMouse)
			{
				this->position += (saveMouse - currentMouse) / zoomFactor;
				this->UpdateRenderRect();
				saveMouse = currentMouse;
			}
		}
		saveMouse = currentMouse;
	}
}
/***************************************************************************
## UpdateTargetCameraMode ##

***************************************************************************/
void CameraManager::UpdateTargetCameraMode()
{
	if (pTarget)
	{
		{
			//target�� ��ġ�� ������ �����δ�.
			Vector2 centerPos = { position.x + CastingFloat(WinSizeX) * 0.5f, position.y + CastingFloat(WinSizeY) * 0.5f };
			Vector2 toTarget = pTarget->GetPosition() - centerPos;

			switch (state)
			{
			case MoveState::None:
			{
				if (toTarget.GetLength() > moveStartDistance)
				{
					this->state = MoveState::MoveToTarget;
				}
			}
			break;

			case MoveState::MoveToTarget:
			{
				float length = toTarget.GetLength();
				this->speed = (length / (CameraMaxDistance - CameraMinDistance)) * (CameraMaxSpeed - CameraMinSpeed);
				this->speed = Math::Clampf(speed, CameraMinSpeed, CameraMaxSpeed);

				centerPos += toTarget.Normalize() * speed * _TimeManager->DeltaTime();
				this->position = centerPos - Vector2(WinSizeX / 2.f, WinSizeY / 2.f);
				this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));

				if ((pTarget->GetPosition() - centerPos).GetLength() <= 50.f)
				{
					this->state = MoveState::None;
					this->position = centerPos - Vector2(WinSizeX / 2.f, WinSizeY / 2.f);
					this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));
				}

				this->AmendCamera();

			}
			break;
			}
		}
		if(isShake == true)
		{
			shakeDirection = -1.f * shakeDirection;
			shakeTime -= _TimeManager->DeltaTime();
			shakeStrength -= (shakeTime / totalShakeTime) *_TimeManager->DeltaTime();
			float strengh = shakeStrength * shakeDirection;
			position += Vector2(0.f, strengh);
			this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));
			
			if (shakeTime <= 0.f)
			{
				isShake = false;
			}
			this->AmendCamera();
		}
	}
}

void CameraManager::AmendCamera()
{
	if (position.x < 0.f)
	{
		position.x -= position.x;
		this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));
	}
	else if (cameraRect.right > (LONG)mapSize.x)
	{
		position.x -= ((float)cameraRect.right) - mapSize.x;
		this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));
	}
	if (cameraRect.top < 0)
	{
		position.y -= position.y;
		this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));
	}
	else if (cameraRect.bottom > (LONG)mapSize.y)
	{
		position.y -= (float(cameraRect.bottom)) - mapSize.y;
		this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));
	}
}

/***************************************************************************
## CameraProc ## 
���콺 �ٿ� ���� ��
***************************************************************************/
void CameraManager::CameraProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (state == MoveState::FreeCamera)
	{
		if (IsMouseOnGui == false)
		{
			if ((SHORT)HIWORD(wParam) > 0)
			{
				this->zoomFactor += 0.1f;
				this->zoomFactor = Math::Clampf(zoomFactor, CameraZoomMin, CameraZoomMax);
			}
			else
			{
				this->zoomFactor -= 0.1f;
				this->zoomFactor = Math::Clampf(zoomFactor, CameraZoomMin, CameraZoomMax);
			}
		}
	}
}

void CameraManager::SetTarget(GameObject * object)
{
	if (object)
	{
		this->pTarget = object;
		this->state = MoveState::None;
		this->position = object->GetPosition() - Vector2(WinSizeX/2,WinSizeY/2);
		this->cameraRect = Figure::RectMake(position, Vector2(WinSizeX, WinSizeY));
		this->AmendCamera();
	}
}

void CameraManager::Shake(float strength,float shakeTime)
{
	if (isShake == false)
	{
		this->isShake = true; 
		this->shakeStrength = strength;
		this->shakeTime = this->totalShakeTime = shakeTime;
	}
}

void CameraManager::InitCameraToPlayer()
{
	GameObject* object = _ObjectManager->FindObject(ObjectType::Object, "Will");
	if (object)
	{
		this->SetTarget(object);
	}
}
