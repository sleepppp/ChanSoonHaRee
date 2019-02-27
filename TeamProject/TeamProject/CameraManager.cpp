#include "stdafx.h"
#include "CameraManager.h"

SingletonCpp(CameraManager)

/***************************************************************************
## CameraManager ## 
***************************************************************************/
CameraManager::CameraManager()
	:mapSize((float)WinSizeX,(float)WinSizeY),pTarget(nullptr),zoomFactor(1.0f),
	speed(100.0f), state(CameraManager::FreeCamera)
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
	case CameraManager::FollowTarget:
		break;
	case CameraManager::MoveToTarget:
		break;
	case CameraManager::FreeCamera:
		this->UpdateFreeCameraMode();
		break;
	case CameraManager::End:
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
	ImGui::Begin("Camera");
	{
		ImGui::Text("Camera Position : %f , %f", this->position.x, this->position.y);
		ImGui::Text("Caemra Zoom : %f", this->zoomFactor);
		ImGui::InputFloat2("MapSize", &mapSize.x);
		ImGui::InputFloat("CameraSpeed", &this->speed);

		if (ImGui::Button("ResetCamera"))
			this->SetPosition(Vector2(0.f, 0.f));
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
## CameraProc ## 
���콺 �ٿ� ���� ��
***************************************************************************/
void CameraManager::CameraProc(UINT message, WPARAM wParam, LPARAM lParam)
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
