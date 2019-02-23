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
/***********************************************
## AddObject ##
@@ ObjectType::Enum type : 오브젝트 담을 벡터 카테고리 Enum 
@@ GameObject* object : 담을 오브젝트 
************************************************/
void ObjectManager::AddObject(ObjectType::Enum type, GameObject * gameObject)
{
	//ObjectIter iter = objectContainer.find(type);
	//if (iter != objectContainer.end())
	//{
	//	iter->second.push_back(gameObject);
	//}
	
	//맵도 키값을 통해 배열처럼 접근 가능(find처럼 내부적으로 이진탐색 알고리즘으로 탐색한다)
	//문제는 해당 키값이 없을 경우 빈 방을 생성하고 data값을 0으로 초기화 한다. 
	//고로 키값이 없을 때 빈방을 만들어 버리므로 조심해야한다. 
	objectContainer[type].push_back(gameObject);
}
/***********************************************
## FindObject ##
@@ ObjectType::Enum type : 찾을 오브젝트 카테고리 enum 
@@ string name : 찾을 오브젝트 이름 

오브젝트 타입 벡터내에서 찾아서 반환 
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
@@ string name : 찾을 오브젝트 이름 

전체 오브젝트 컨테이너를 뒤져서 찾는다. 
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
@@ ObjectType::Enum type : 찾을 오브젝트 카테고리 
@@ string name : 찾을 오브젝트 이름 

같은 이름의 오브젝트를 전부 찾아서 벡터에 담아 반환 
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
@@ ObjectType::Enum type : 오브젝트 타입 

해당 오브젝트 타입 벡터 전부 반환
************************************************/
vector<class GameObject*> ObjectManager::GetObjectList(ObjectType::Enum type)
{
	return objectContainer[type];
}
