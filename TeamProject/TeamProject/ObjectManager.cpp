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

}

/***************************************************************************************
## ~ObjectManager ## 
****************************************************************************************/
ObjectManager::~ObjectManager()
{
	//������Ʈ ���� Ŭ���� ~(Ȥ�� ����)
	objectList.clear();
}
/***************************************************************************************
## Init ## 
��ü ������Ʈ Init ȣ�� 
****************************************************************************************/
void ObjectManager::Init()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		objectList[i]->Init();
	}
}
/***************************************************************************************
## Release ##
��ü ������Ʈ �Ҵ� ���� 
****************************************************************************************/
void ObjectManager::Release()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		objectList[i]->Release();
		SafeDelete(objectList[i]);
	}
	objectList.clear();
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
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//���� ������Ʈ�� isLive���� false��� �׾��ٴ� ���̹Ƿ� 
		if (objectList[i]->GetIsLive() == false)
		{
			//������Ʈ Relase�� �Ҵ�����, ���Ϳ��� ���ű��� ���ش�. 
			objectList[i]->Release();
			SafeDelete(objectList[i]);
			objectList.erase(objectList.begin() + i);
			i--;
			//��� ���� ������ �����ٸ� �Ʒ��� �ִ� �ڵ�� ����Ǹ� �ȵǹǷ� continue;
			continue;
		}
		//���� ������Ʈ�� ����ְ� Ȱ�����°� true��� ������Ʈ �ض� 
		if (objectList[i]->GetActive() == true)
		{
			objectList[i]->Update();
		}
	}
}
/***************************************************************************************
## Render ##
��� ������Ʈ ������ 
****************************************************************************************/
void ObjectManager::Render()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//���� �ش� ������Ʈ�� Ȱ��ȭ�� �Ǿ��ִٸ� ������ �ض�
		if (objectList[i]->GetActive())
			objectList[i]->Render();
	}
}
/***************************************************************************************
## AddObject ## 
@@ GameObject* object : ����� ������Ʈ 
****************************************************************************************/
void ObjectManager::AddObject(GameObject * object)
{
	objectList.push_back(object);
}
/***************************************************************************************
## FindObject ## 
@@ string name : ã�� ������Ʈ �̸� 

@@ return GameObject* : ã�� ������Ʈ ������ ��ȯ(���� ��ã�Ҵٸ� nullptr��ȯ)
****************************************************************************************/
GameObject * ObjectManager::FindObject(string name)
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//���� ������Ʈ�� �̸��̶� ã������ �̸��̶� ���ٸ� 
		if (objectList[i]->GetName() == name)
		{
			//�ش� ������Ʈ ��ȯ�ض� 
			return objectList[i];
		}
	}
	//������� �Դٸ� ��ã���� nullptr ��ȯ 
	return nullptr;
}
/***************************************************************************************
## FindObjects ##
�ش� �̸��� ������Ʈ�� ���� ã�Ƽ� ��ȯ
@@ string name : ã�� ������Ʈ�� �̸� 

@@ return vector<GameObject*> : ã�� ������Ʈ�� ����ִ� ���� 
****************************************************************************************/
vector<class GameObject*> ObjectManager::FindObjects(string name)
{
	//ã�� ������Ʈ�� ���� ���� 
	vector<GameObject*> findList;
	
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//���� ã������ ������Ʈ�� �ش� ������Ʈ�� �̸��� ���ٸ� 
		if (objectList[i]->GetName() == name)
		{
			//���Ϳ� ��´�
			findList.push_back(objectList[i]);
		}
	}
	//ã�� �༮�� ���� ��Ƽ� ��ȯ 
	return findList;
}
/***************************************************************************************
## GetObjectList ## 
��� ������Ʈ ����Ʈ ��ȯ
****************************************************************************************/
vector<class GameObject*> ObjectManager::GetObjectList()
{
	return objectList;
}
