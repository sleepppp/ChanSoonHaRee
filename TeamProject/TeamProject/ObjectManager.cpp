#include "stdafx.h"
#include "ObjectManager.h"
#include "GameObject.h"

//������ �̱��� CPP�κ� 
SingletonCpp(ObjectManager)
/***************************************************************************************
## ObjectManager ## 
������ 
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
��ü ������Ʈ Init ȣ�� 
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
��ü ������Ʈ �Ҵ� ���� 
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
��ü ������Ʈ ������Ʈ �� �׾��� �� ���� ����
������Ʈ�� �ı��ϰ� ������ GameObject->isLive���� false�� �ٲ��ָ� �ȴ�. 
���Ѱ� ������ �� �����Ӹ��� Active�� Live�˻縦 �����ϱ� ������ ���߿� �ڵ忡 ���� 
���ذ� �� �������ø� ��� �����ؼ� �˷��帱 ���� 
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
��� ������Ʈ ������ 
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
