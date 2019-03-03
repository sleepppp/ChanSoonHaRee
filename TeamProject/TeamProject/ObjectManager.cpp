#include "stdafx.h"
#include "ObjectManager.h"

#include "GameObject.h"
#include "LightSystem.h"

#include <algorithm>
#include <unordered_map> 

SingletonCpp(ObjectManager)

/*********************************************************************
## ObjectManager ##
�̸� ī�װ� ���� ���� �־���. 
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
��� ������Ʈ�� �޸� ���� �� �����̳ʵ� ����ش�. 
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
��� ������Ʈ �Ҵ� ����, �� ���� clear(�̶� ���� clear���ָ� �ȵȴ�) 
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
@@ ObjectType::Enum type : ������Ʈ Ÿ�� 
@@ GameObject* pObject : ������Ʈ 
**********************************************************************/
void ObjectManager::AddObject(const ObjectType::Enum type, GameObject* pObject)
{
	this->_objectContainer[type].push_back(pObject);
}
/*********************************************************************
## FindObject ##
@@ ObjectType::Enum type : Ÿ�� 
@@ string name : ã�� ������Ʈ �̸� 
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
@@ ObjectType::Enum type : ã�� ������Ʈ Ÿ�� 
@@ string name : �̸� 
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
@@ ObjectType::Enum type : ������Ʈ Ÿ��
**********************************************************************/
vector<class GameObject*> ObjectManager::GetObjectList(const ObjectType::Enum type)
{
	return _objectContainer[type];
}

