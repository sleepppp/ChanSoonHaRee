#include "stdafx.h"
#include "Dungeon_Map_01.h"
#include "Image.h"
#include "GameObject.h"

void Dungeon_Map_01::Init()
{
	_ObjectManager->AddObject(ObjectType::Object, new GameObject());

	_ImageManager->AddImage("mpa01", L"../Resources/Scene/Dungeon_Map_01.png");

	
	_object->Init();
}

void Dungeon_Map_01::Release()
{
	_object->Release();
}

void Dungeon_Map_01::Update()
{
	_object->Update();
}

void Dungeon_Map_01::Render()
{
	_object->Render();
}

Dungeon_Map_01::Dungeon_Map_01(Vector2 pos, Vector2 size)
{
	_object->SetPosition((pos.x, pos.y));
	_object->SetSize((size.x, size.y/*1152, 90*/));
	Pivot::LEFT_TOP;

}


Dungeon_Map_01::~Dungeon_Map_01()
{
}
