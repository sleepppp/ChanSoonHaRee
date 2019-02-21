#pragma once
/***************************************************************************************
## ObjectManager ##
모든 GameObject 관리할 클래스 
****************************************************************************************/
class ObjectManager
{
	//전처리기 싱글톤 
	SingletonHeader(ObjectManager)
private:
	//모든 오브젝트들 담을 벡터
	vector<class GameObject*> objectList;
public:
	void Init();
	void Release();
	void Update();
	void Render();
	
	void AddObject(class GameObject* object);				//오브젝트 등록 
	class GameObject* FindObject(string name);				//오브젝트를 이름으로 찾아서 반환 
	vector<class GameObject*> FindObjects(string name);		//같은 이름의 오브젝트를 전부 찾아서 벡터에 담아서 반환
	vector<class GameObject*> GetObjectList();				//모든 오브젝트 리스트 반환

};

#define _ObjectManager ObjectManager::Get()