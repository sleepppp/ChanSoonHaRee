#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"
#include "LightSystem.h"

#include <algorithm>
#include <unordered_map> 

SingletonCpp(ObjectManager)

/*********************************************************************
## ObjectManager ##
미리 카테고리 별로 벡터 넣어논다. 
**********************************************************************/
ObjectManager::ObjectManager()
	:_isZorder(false)
{
	for (UINT i = 0; i < ObjectType::End; ++i)
	{
		_objectContainer.insert(make_pair((ObjectType::Enum)i, vector<GameObject*>()));
	}
	_lightSystem = new LightSystem;

}
/*********************************************************************
## ~ObjectManager ##
모든 오브젝트들 메모리 해제 및 컨테이너도 비워준다. 
**********************************************************************/
ObjectManager::~ObjectManager()
{
	SafeDelete(_lightSystem);

	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);
		}
		iter->second.clear();
	}
	_objectContainer.clear();
}
/*********************************************************************
## Init ##
**********************************************************************/
void ObjectManager::Init()
{
	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Init();
		}
	}
}
/*********************************************************************
## Release ##
모든 오브젝트 할당 해제, 및 벡터 clear(이때 맵은 clear해주면 안된다) 
**********************************************************************/
void ObjectManager::Release()
{
	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			iter->second[i]->Release();
			SafeDelete(iter->second[i]);
		}
		iter->second.clear();
	}
}
/*********************************************************************
## Update ##
**********************************************************************/
void ObjectManager::Update()
{
	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetLive() == false)
			{
				iter->second[i]->Release();
				SafeDelete(iter->second[i]);
				iter->second.erase(iter->second.begin() + i--);
				continue; 
			}
			if (iter->second[i]->GetActive())
			{
				iter->second[i]->Update();
			}
		}
	}
}
/*********************************************************************
## Render ##
**********************************************************************/
void ObjectManager::Render()
{
	if(_isZorder)
		this->ZOrder();

	ObjectContainerIter iter = _objectContainer.begin();
	for (; iter != _objectContainer.end(); ++iter)
	{
		for (UINT i = 0; i < iter->second.size(); ++i)
		{
			if (iter->second[i]->GetActive())
			{
				iter->second[i]->Render();
			}
		}
	}
}
/*********************************************************************
## AddObject ##
@@ ObjectType::Enum type : 오브젝트 타입 
@@ GameObject* pObject : 오브젝트 
**********************************************************************/
void ObjectManager::AddObject(const ObjectType::Enum type, GameObject* pObject)
{
	this->_objectContainer[type].push_back(pObject);
}
/*********************************************************************
## FindObject ##
@@ ObjectType::Enum type : 타입 
@@ string name : 찾을 오브젝트 이름 
**********************************************************************/
 GameObject* ObjectManager::FindObject(const ObjectType::Enum type, const string name)
{
	ObjectContainerIter iter = _objectContainer.find(type);
	for (UINT i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			return iter->second[i];
		}
	}
	return nullptr;
}
/*********************************************************************
## FindObjects ##
@@ ObjectType::Enum type : 찾을 오브젝트 타입 
@@ string name : 이름 
**********************************************************************/
vector<class GameObject*> ObjectManager::FindObjects(const ObjectType::Enum type, const string name)
{
	vector<GameObject*> findList;
	ObjectContainerIter iter = _objectContainer.find(type);
	for (UINT i = 0; i < iter->second.size(); ++i)
	{
		if (iter->second[i]->GetName() == name)
		{
			findList.push_back(iter->second[i]);
		}
	}

	return findList;
}
/*********************************************************************
## GetObjectList ##
@@ ObjectType::Enum type : 오브젝트 타입
**********************************************************************/
vector<class GameObject*> ObjectManager::GetObjectList(const ObjectType::Enum type)
{
	return _objectContainer[type];
}

