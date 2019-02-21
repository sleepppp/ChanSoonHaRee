#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"
SingletonCpp(ObjectManager)

ObjectManager::ObjectManager()
{

}


ObjectManager::~ObjectManager()
{
	objectList.clear();
}

void ObjectManager::Init()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		objectList[i]->Init();
	}
}

void ObjectManager::Release()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		objectList[i]->Release();
		SafeDelete(objectList[i]);
	}
	objectList.clear();
}

void ObjectManager::Update()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetIsLive() == false)
		{
			objectList[i]->Release();
			SafeDelete(objectList[i]);
			objectList.erase(objectList.begin() + i);
			i--;
			continue;
		}

		if (objectList[i]->GetActive() == true)
		{
			objectList[i]->Update();
		}
	}
}

void ObjectManager::Render()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetActive())
			objectList[i]->Render();
	}
}

void ObjectManager::AddObject(GameObject * object)
{
	objectList.push_back(object);
}

GameObject * ObjectManager::FindObject(string name)
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == name)
		{
			return objectList[i];
		}
	}
	//여기까지 왔다면 못찾은것
	return nullptr;
}

vector<class GameObject*> ObjectManager::FindObjects(string name)
{
	vector<GameObject*> findList;

	for (UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == name)
		{
			findList.push_back(objectList[i]);
		}
	}

	return findList;
}

vector<class GameObject*> ObjectManager::GetObjectList()
{
	return objectList;
}
