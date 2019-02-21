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

}

/***************************************************************************************
## ~ObjectManager ## 
****************************************************************************************/
ObjectManager::~ObjectManager()
{
	//오브젝트 벡터 클리어 ~(혹시 몰라서)
	objectList.clear();
}
/***************************************************************************************
## Init ## 
전체 오브젝트 Init 호출 
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
전체 오브젝트 할당 해제 
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
전체 오브젝트 업데이트 및 죽었을 때 해제 까지
오브젝트를 파괴하고 싶으면 GameObject->isLive값만 false로 바꿔주면 된다. 
편한것 같지만 매 프레임마다 Active및 Live검사를 수행하기 때문에 나중에 코드에 대한 
이해가 더 높아지시면 계속 개조해서 알려드릴 예정 
****************************************************************************************/
void ObjectManager::Update()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//만약 오브젝트의 isLive값이 false라면 죽었다는 뜻이므로 
		if (objectList[i]->GetIsLive() == false)
		{
			//오브젝트 Relase및 할당해제, 벡터에서 제거까지 해준다. 
			objectList[i]->Release();
			SafeDelete(objectList[i]);
			objectList.erase(objectList.begin() + i);
			i--;
			//모든 제거 과정이 끝났다면 아래에 있는 코드는 실행되면 안되므로 continue;
			continue;
		}
		//만약 오브젝트가 살아있고 활성상태가 true라면 업데이트 해라 
		if (objectList[i]->GetActive() == true)
		{
			objectList[i]->Update();
		}
	}
}
/***************************************************************************************
## Render ##
모든 오브젝트 렌더링 
****************************************************************************************/
void ObjectManager::Render()
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//만약 해당 오브젝트가 활성화가 되어있다면 렌더링 해라
		if (objectList[i]->GetActive())
			objectList[i]->Render();
	}
}
/***************************************************************************************
## AddObject ## 
@@ GameObject* object : 등록할 오브젝트 
****************************************************************************************/
void ObjectManager::AddObject(GameObject * object)
{
	objectList.push_back(object);
}
/***************************************************************************************
## FindObject ## 
@@ string name : 찾을 오브젝트 이름 

@@ return GameObject* : 찾은 오브젝트 포인터 반환(만약 못찾았다면 nullptr반환)
****************************************************************************************/
GameObject * ObjectManager::FindObject(string name)
{
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//만약 오브젝트의 이름이랑 찾을려는 이름이랑 같다면 
		if (objectList[i]->GetName() == name)
		{
			//해당 오브젝트 반환해라 
			return objectList[i];
		}
	}
	//여기까지 왔다면 못찾은것 nullptr 반환 
	return nullptr;
}
/***************************************************************************************
## FindObjects ##
해당 이름의 오브젝트를 전부 찾아서 반환
@@ string name : 찾을 오브젝트들 이름 

@@ return vector<GameObject*> : 찾은 오브젝트들 담겨있는 벡터 
****************************************************************************************/
vector<class GameObject*> ObjectManager::FindObjects(string name)
{
	//찾은 오브젝트들 담을 벡터 
	vector<GameObject*> findList;
	
	for (UINT i = 0; i < objectList.size(); ++i)
	{
		//만약 찾을려는 오브젝트랑 해당 오브젝트랑 이름이 같다면 
		if (objectList[i]->GetName() == name)
		{
			//벡터에 담는다
			findList.push_back(objectList[i]);
		}
	}
	//찾은 녀석들 전부 담아서 반환 
	return findList;
}
/***************************************************************************************
## GetObjectList ## 
모든 오브젝트 리스트 반환
****************************************************************************************/
vector<class GameObject*> ObjectManager::GetObjectList()
{
	return objectList;
}
