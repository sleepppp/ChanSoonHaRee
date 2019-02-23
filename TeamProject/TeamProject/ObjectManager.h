#pragma once
/***************************************************************************************
## ObjectManager ##
모든 GameObject 관리할 클래스 
****************************************************************************************/
namespace ObjectType
{
	enum Enum
	{
		BackGround,Object,UI,End
	};
}
class ObjectManager
{
	//전처리기 싱글톤 
	SingletonHeader(ObjectManager)
private:
	typedef vector<class GameObject*> ObjectList;
	typedef map<ObjectType::Enum, ObjectList>::iterator ObjectIter;
private:
	map<ObjectType::Enum, ObjectList> objectContainer;
public:
	void Init();
	void Release();
	void Update();
	void Render();
	
	void AddObject(ObjectType::Enum type, class GameObject* gameObject);
	class GameObject* FindObject(ObjectType::Enum type, string name);
	class GameObject* FindObject(string name);
	vector<class GameObject*> FindObjects(ObjectType::Enum type, string name);
	vector<class GameObject*> GetObjectList(ObjectType::Enum type);
};

#define _ObjectManager ObjectManager::Get()