#include "stdafx.h"
#include "Dungeon_Map_Boss.h"


Dungeon_Map_Boss::Dungeon_Map_Boss()
{
}


Dungeon_Map_Boss::~Dungeon_Map_Boss()
{
}

void Dungeon_Map_Boss::Init()
{
	this->HaInit();
	this->ReeInit();
	this->ChanInit();
	this->SoonInit();
	_ObjectManager->Init();

	_map = _ImageManager->AddImage("BoosRoom", L"../Resources/Scene/BossRoom.png", true);
	_Camera->SetMapSize(Vector2((float)_map->GetWidth(), (float)_map->GetHeight()));
	_Camera->InitCameraToPlayer();
}

void Dungeon_Map_Boss::Release()
{
	_ObjectManager->Release();
}

void Dungeon_Map_Boss::Update()
{
	_ObjectManager->Update();
}

void Dungeon_Map_Boss::Render()
{
	_map->Render(0, 0, Pivot::LEFT_TOP, true);
	_ObjectManager->Render();
}
