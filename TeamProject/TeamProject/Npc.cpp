#include "stdafx.h"
#include "Npc.h"
#include "Time.h"
#include "Image.h"
#include "Animation.h"
using namespace Figure;

Npc::Npc()
{
	//_name = "NpcKid";
	movePoint.push_back(Vector2(794,787));
	movePoint.push_back(Vector2(2187,787));
	movePoint.push_back(Vector2(2187,1585));
	movePoint.push_back(Vector2(794,1585));

	_ImageManager->AddFrameImage("Kids", L"../Resources/Npc/Kids.png", 6, 4);
	_ImgKids = _ImageManager->FindImage("Kids");

	this->_isActive = true;
	this->_pivot = Pivot::CENTER;
	_position = movePoint[0];
	_size = Vector2(100, 100);
	
	this->UpdateMainRect();
	_speed = 40.f;
	_index = 1;
	_frameX=0;
	_frameY=3;
	_count = 0;
}

Npc::~Npc()
{
}

void Npc::Init()
{	

}

void Npc::Release()
{

}

void Npc::Update()
{
	float angle;	
	angle = Math::GetAngle(_position.x, _position.y, movePoint[_index].x, movePoint[_index].y);
	  
	_position.x += cos(angle)*_speed*_TimeManager->DeltaTime();
	_position.y -= sin(angle)*_speed*_TimeManager->DeltaTime();

	

	float distance = Math::GetDistance(_position.x, _position.y, movePoint[_index].x, movePoint[_index].y);
	if (distance <= 5.0f)
	{		
		_index++;
		if (movePoint.size() == _index)
		{
			_index = 0;
		}
	}

	_count += _TimeManager->DeltaTime();
	if(_count > 0.3f)
	{
		if (_frameX > 4)
		{
			_frameX = 0;
		}
		else
		{
			_frameX++;
		}		
		_count = 0.0f;
	}
	
	if (_index == 0) _frameY = 1;
	if (_index == 1) _frameY = 3;
	if (_index == 2) _frameY = 0;
	if (_index == 3)_frameY = 2;

	this->UpdateMainRect();
}

void Npc::Render()
{
	//_DXRenderer->FillRectangle(_npcRc, DefaultBrush::red, true);
	_ImgKids->SetSize(Vector2(60,60));
	_ImgKids->SetScale(1.0f);
	_ImgKids->FrameRender(_position.x, _position.y, _frameX, _frameY, Pivot::CENTER, true);

	//ImGui::Begin("aa");
	//ImGui::Text("%d, %d", _Camera->GetWorldMousePoint().x, _Camera->GetWorldMousePoint.y);
	//ImGui::End();

}

