#include "stdafx.h"
#include "Dungeon_Map_02.h"
#include "GameObject.h"
#include "Image.h"
#include "LoadingScene.h"
#include "Player.h"
#include "Door.h"

Dungeon_Map_02::Dungeon_Map_02()
{
}


Dungeon_Map_02::~Dungeon_Map_02()
{
}

void Dungeon_Map_02::Init()
{
	_closeDoorCount = 0;
	_timeCount = 0.f;
	_isTransScene = false;
	
	_map = _ImageManager->AddImage("map02", L"../Resources/Scene/Dungeon_Map_02.bmp");
	
	_ObjectManager->AddObject(ObjectType::Object, new Player());

	GameObject* object = new GameObject;
	object->SetPosition(Vector2(0, 0));
	object->SetSize(Vector2(WinSizeX, 90));
	object->SetPivot(Pivot::LEFT_TOP);
	_ObjectManager->AddObject(ObjectType::Object, object);
	
	GameObject* object1 = new GameObject;
	object1->SetPosition(Vector2(0, WinSizeY - 90));
	object1->SetSize(Vector2(WinSizeX, 90));
	object1->SetPivot(Pivot::LEFT_TOP);
	_ObjectManager->AddObject(ObjectType::Object, object1);
	
	GameObject* object2 = new GameObject;
	object2->SetPosition(Vector2(0, 0));
	object2->SetSize(Vector2(90, WinSizeY));
	object2->SetPivot(Pivot::LEFT_TOP);
	_ObjectManager->AddObject(ObjectType::Object, object2);
	
	GameObject* object3 = new GameObject;
	object3->SetPosition(Vector2(WinSizeX - 90, 0));
	object3->SetSize(Vector2(90, WinSizeY));
	object3->SetPivot(Pivot::LEFT_TOP);
	_ObjectManager->AddObject(ObjectType::Object, object3);
	
	Door* _door = new Door(Vector2((WinSizeX / 2 - 90), 0), Vector2(155, 100));
	_ObjectManager->AddObject(ObjectType::Object, _door);

	_ObjectManager->Init();
}

void Dungeon_Map_02::Release()
{
	_ObjectManager->Release();
}
void Dungeon_Map_02::Update()
{

	_ObjectManager->Update();
}
void Dungeon_Map_02::Render()
{
	_map->Render(0, 0, Pivot::LEFT_TOP, true);
	_ObjectManager->Render();
}