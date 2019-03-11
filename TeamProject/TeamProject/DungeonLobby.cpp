#include "stdafx.h"
#include "DungeonLobby.h"


void DungeonLobby::Init()
{
	_background = _ImageManager->FindImage("Dungeon_Lobby");
	this->SoonInit();
	this->ReeInit();
	this->HaInit();
	this->ChanInit();

	_ObjectManager->Init();
	_Camera->SetMapSize(Vector2(CastingInt(_background->GetWidth()), CastingInt(_background->GetHeight())));
	_Camera->InitCameraToPlayer();
}

void DungeonLobby::Release()
{
	_ObjectManager->Release();
}

void DungeonLobby::Update()
{
	_ObjectManager->Update();
}

void DungeonLobby::Render()
{
	_background->Render(0, 0, Pivot::LEFT_TOP, true);
	_ObjectManager->Render();
}

void DungeonLobby::ChanInit()
{
}

void DungeonLobby::HaInit()
{
}

void DungeonLobby::ReeInit()
{
}
