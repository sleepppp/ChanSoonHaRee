#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"
#include "Dungeon_Map_Boss.h"
#include "Dungeon_Map_02.h"
#include "TestPlayer.h"
#include "TestInventory.h"

#include "StaticObject.h"
#include "DebugCollider.h"
#include "FrameObject.h"
#include "Tree.h"
#include "Program.h"

void Program::LoadResourceSoon()
{
	_ImageManager->AddImage("Shadow", L"../Resources/Object/Shadow.png");
	_ImageManager->AddImage("build_Retaile", PathResources(L"Object/build_Retaile.png"));
	_ImageManager->AddImage("build_Enchant", PathResources(L"Object/build_Enchant.png"));
	_ImageManager->AddImage("build_fountain", PathResources(L"Object/build_fountain.png"));
	_ImageManager->AddImage("build_Top1", PathResources(L"Object/build_Top1.png"));
	_ImageManager->AddImage("build_Shop", PathResources(L"Object/build_Shop.png"));
	_ImageManager->AddImage("build_Board", PathResources(L"Object/build_Board.png"));
	_ImageManager->AddImage("build_Bottom1", PathResources(L"Object/build_Bottom1.png"));
	_ImageManager->AddImage("build_Bottom2", PathResources(L"Object/build_Bottom2.png"));
	_ImageManager->AddImage("build_Forge", PathResources(L"object/build_Forge.png"));
	_ImageManager->AddImage("build_Bottom3", PathResources(L"Object/build_Bottom3.png"));
	_ImageManager->AddFrameImage("tree", PathResources(L"Object/tree.png"), 4, 1);
	_ImageManager->AddFrameImage("RivalFauntain", PathResources(L"Object/RivalFauntain.png"), 9, 1);

	_ImageManager->AddImage("LeftDoor", PathResources(L"Scene/door_left.png"));
	_ImageManager->AddImage("RightDoor", PathResources(L"Scene/door_right.png"));
	_ImageManager->AddImage("TitleImage", PathResources(L"Scene/logo.png"));
	_ImageManager->AddImage("Selector", PathResources(L"Scene/Selector.png"));
	_ImageManager->AddFrameImage("door_light", PathResources(L"Scene/door_light.png"), 30, 1, false);

	_SoundManager->AddSound("DoorOpen", PathSounds("door.wav"));
	_SoundManager->AddSound("introBGM", PathSounds("introBGM.mp3"), true, true);
	_SoundManager->SetMusicVolume(0.1f);
}


void MainScene::SoonInit()
{

}
void Dungeon_Map_01::SoonInit()
{

}
void Dungeon_Map_Boss::SoonInit()
{

}
void TownScene::SoonInit()
{

	StaticObject* tempObject = nullptr;
	tempObject = new StaticObject("build_Retaile", Vector2(20, 290));
	tempObject->SetCollisionRect({ 314,312,650,676 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Enchant", Vector2(50, 1298));
	tempObject->SetCollisionRect({ 85,1580,641,2050 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Top1", Vector2(1092, 236));
	tempObject->SetCollisionRect({ 1100,306,1417,622 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Shop", Vector2(1620, 194));
	tempObject->SetCollisionRect({ 1619,303,2148,626 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Board", Vector2(1574, 1078));
	tempObject->SetCollisionRect({ 1599,1100,1759,1214 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Bottom1", Vector2(762, 1652));
	tempObject->SetCollisionRect({ 909,1678,1229,1981 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Bottom2", Vector2(1725, 1545));
	tempObject->SetCollisionRect({ 1737,1619,2057,1927 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Forge", Vector2(2298, 786));
	tempObject->SetCollisionRect({ 2328,876,2934,1270 });
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	tempObject = new StaticObject("build_Bottom3", Vector2(2369, 1405));
	_ObjectManager->AddObject(ObjectType::Object, tempObject);

	FrameObject* rival = new FrameObject("RivalFauntain", Vector2(467, 923));
	rival->SetPivot(Pivot::CENTER);
	rival->SetSize(Vector2(128, 128));
	rival->SetCollisionRect({ 440,894,497,952 });
	_ObjectManager->AddObject(ObjectType::Object, rival);

	Tree* tempFrameObject = nullptr;

	tempFrameObject = new Tree(Vector2(912, 306));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(912, 606));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(442, 306));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(990, 1000));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(990, 1460));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(2014, 1000));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(2014, 1460));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(2368, 556));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	tempFrameObject = new Tree(Vector2(2201, 1868));
	_ObjectManager->AddObject(ObjectType::Object, tempFrameObject);

	//_ObjectManager->AddObject(ObjectType::UI, new DebugCollider);

}



void Dungeon_Map_02::SoonInit()
{
}
