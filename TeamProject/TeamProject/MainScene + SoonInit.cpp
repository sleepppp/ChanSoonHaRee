#include "stdafx.h"
#include "MainScene.h"
#include "TownScene.h"
#include "Dungeon_Map_01.h"

#include "TestPlayer.h"
#include "TestInventory.h"
void MainScene::SoonInit()
{
	//_ObjectManager->AddObject(ObjectType::Object, new TestPlayer);

	//_ObjectManager->AddObject(ObjectType::UI, new TestInventory);
}
void Dungeon_Map_01::SoonInit()
{
	_ObjectManager->AddObject(ObjectType::UI, new TestInventory);
}
void TownScene::SoonInit()
{

}