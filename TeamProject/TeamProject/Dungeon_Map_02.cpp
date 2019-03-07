#include "stdafx.h"
#include "Dungeon_Map_02.h"
#include "GameObject.h"
#include "Image.h"
#include "LoadingScene.h"

Dungeon_Map_02::Dungeon_Map_02()
{
}


Dungeon_Map_02::~Dungeon_Map_02()
{
}

void Dungeon_Map_02::Init()
{
	_map = _ImageManager->AddImage("map02", L"../Resources/Scene/Dungeon_Map_02.bmp");
	_door = _ImageManager->AddFrameImage("door", L"../Resources/Object/door.png", 5, 1);
}

void Dungeon_Map_02::Release()
{

}
void Dungeon_Map_02::Update()
{

}
void Dungeon_Map_02::Render()
{

}