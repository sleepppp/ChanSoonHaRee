#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"

//디파인 싱글톤 CPP부분 
SingletonCpp(ObjectManager)
/***************************************************************************************
## ObjectManager ## 
생성자 
****************************************************************************************/
ObjectManager::ObjectManager()
{
	for (UINT i = 0; i < ObjectType::End; ++i)
	{
		vector<GameObject*> emptyVector;
		objectContainer.insert(make_pair((ObjectType::Enum)i, emptyVector));
	}
}

/***************************************************************************************
## ~ObjectManager ## 
****************************************************************************************/
ObjectManager::~ObjectManager()
{
	objectContainer.clear();
}
/***************************************************************************************
## Init ## 
전체 오브젝트 Init 호출 
****************************************************************************************/
void ObjectManager::Init()
{
	ObjectIter iter = objectContainer.begin();
	for (; iter != objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Init();
		}
	}
}
/***************************************************************************************
## Release ##
전체 오브젝트 할당 해제 
****************************************************************************************/
void ObjectManager::Release()
{
	ObjectIter iter = objectContainer.begin();
	for (; objectContainer.end() != iter; ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);
		}
		iter->second.clear();
	}
}
/***************************************************************************************
## Update ## 
전체 오브젝트 업데이트 및 죽었을 때 해제 까지
오브젝트를 파괴하고 싶으면 GameObject->isLive값만 false로 바꿔주면 된다. 
편한것 같지만 매 프레임마다 Active및 Live검사를 수행하기 때문에 나중에 코드에 대한 
이해가 더 높아지시면 계속 개조해서 알려드릴 예정 
****************************************************************************************/
void ObjectManager::Update()
{
	ObjectIter iter = objectContainer.begin();
	for (; iter != objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetIsLive() == false)
			{
				iter->second[i]->Release();
				SafeDelete(iter->second[i]);
				iter->second.erase(iter->second.begin() + i);
				--i;
				continue;
			}

			if (iter->second[i]->GetActive() == true)
			{
				iter->second[i]->Update();
			}
		}
	}
}
/***************************************************************************************
## Render ##
모든 오브젝트 렌더링 
****************************************************************************************/
void ObjectManager::Render()
{
	ObjectIter iter = objectContainer.begin();
	for (; iter != objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			if(iter->second[i]->GetActive())
				iter->second[i]->Render();
		}
	}
}

void ObjectManager::AddObject(ObjectType::Enum type, GameObject * gameObject)
{
	//ObjectIter iter = objectContainer.find(type);
	//if (iter != objectContainer.end())
	//{
	//	iter->second.push_back(gameObject);
	//}

	objectContainer[type].push_back(gameObject);
}

GameObject * ObjectManager::FindObject(ObjectType::Enum type, string name)
{
	vector<GameObject*> objectList = objectContainer[type];
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == name)
		{
			return objectList[i];
		}
	}
	return nullptr;
}

GameObject * ObjectManager::FindObject(string name)
{
	ObjectIter iter = objectContainer.begin();
	for (; iter != objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetName() == name)
				return iter->second[i];
		}
	}
	return nullptr;
}

vector<class GameObject*> ObjectManager::FindObjects(ObjectType::Enum type, string name)
{
	vector<GameObject*> findList;

	vector<GameObject*> objectList = objectContainer[type];
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		if (objectList[i]->GetName() == name)
		{
			findList.push_back(objectList[i]);
		}
	}

	return findList;
}

vector<class GameObject*> ObjectManager::GetObjectList(ObjectType::Enum type)
{
	return objectContainer[type];
}
