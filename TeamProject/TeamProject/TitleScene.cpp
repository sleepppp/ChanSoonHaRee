#include "stdafx.h"
#include "TitleScene.h"

#include "LoadingScene.h"
#include "TitleDoor.h"
#include "TitleBackground.h"
#include "TitleLogo.h"
#include "TitleFlowObject.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	_ImageManager->AddImage("LeftDoor", PathResources(L"Scene/door_left.png"));
	_ImageManager->AddImage("RightDoor", PathResources(L"Scene/door_right.png"));
	_ImageManager->AddImage("TitleImage", PathResources(L"Scene/logo.png"));
	_ImageManager->AddImage("Selector", PathResources(L"Scene/Selector.png"));

	_SoundManager->AddSound("DoorOpen", PathSounds("door.wav"));
	_SoundManager->AddSound("introBGM", PathSounds("introBGM.mp3"));
	_SoundManager->SetMusicVolume(0.1f);

	_ObjectManager->AddObject(ObjectType::BackGround, new TitleBackground);
	_ObjectManager->AddObject(ObjectType::Object, new TitleDoor("LeftDoor", Vector2(-1, 0), Vector2(-4, 0), Vector2(WinSizeX / 2, WinSizeY)));
	_ObjectManager->AddObject(ObjectType::Object, new TitleDoor("RightDoor", Vector2(1, 0), Vector2(WinSizeX / 2 + 4, 0), Vector2(WinSizeX / 2, WinSizeY)));
	_ObjectManager->AddObject(ObjectType::Object, new TitleLogo);
	_ObjectManager->AddObject(ObjectType::Object, new TitleFlowObject);

	_ObjectManager->Init();
}

void TitleScene::Release()
{
	_ObjectManager->Release();
}

void TitleScene::Update()
{
	_ObjectManager->Update();
}

void TitleScene::Render()
{
	_ObjectManager->Render();

}
