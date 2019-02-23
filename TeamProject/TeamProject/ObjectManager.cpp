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
/***********************************************
## AddObject ##
@@ ObjectType::Enum type : ������Ʈ ���� ���� ī�װ� Enum 
@@ GameObject* object : ���� ������Ʈ 
************************************************/
void ObjectManager::AddObject(ObjectType::Enum type, GameObject * gameObject)
{
	//ObjectIter iter = objectContainer.find(type);
	//if (iter != objectContainer.end())
	//{
	//	iter->second.push_back(gameObject);
	//}
	
	//�ʵ� Ű���� ���� �迭ó�� ���� ����(findó�� ���������� ����Ž�� �˰������� Ž���Ѵ�)
	//������ �ش� Ű���� ���� ��� �� ���� �����ϰ� data���� 0���� �ʱ�ȭ �Ѵ�. 
	//��� Ű���� ���� �� ����� ����� �����Ƿ� �����ؾ��Ѵ�. 
	objectContainer[type].push_back(gameObject);
}
/***********************************************
## FindObject ##
@@ ObjectType::Enum type : ã�� ������Ʈ ī�װ� enum 
@@ string name : ã�� ������Ʈ �̸� 

������Ʈ Ÿ�� ���ͳ����� ã�Ƽ� ��ȯ 
************************************************/
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
/***********************************************
## FindObject ##
@@ string name : ã�� ������Ʈ �̸� 

��ü ������Ʈ �����̳ʸ� ������ ã�´�. 
************************************************/
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
/***********************************************
## FindObjects ##
@@ ObjectType::Enum type : ã�� ������Ʈ ī�װ� 
@@ string name : ã�� ������Ʈ �̸� 

���� �̸��� ������Ʈ�� ���� ã�Ƽ� ���Ϳ� ��� ��ȯ 
************************************************/
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
/***********************************************
## GetObjectList ##
@@ ObjectType::Enum type : ������Ʈ Ÿ�� 

�ش� ������Ʈ Ÿ�� ���� ���� ��ȯ
************************************************/
vector<class GameObject*> ObjectManager::GetObjectList(ObjectType::Enum type)
{
	return objectContainer[type];
}
