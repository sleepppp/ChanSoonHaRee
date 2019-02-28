#pragma once
/***************************************************************
## ObjectManager ##
������ ������Ʈ �޴����� ����
������ ������ �߰��ϰ� �Ǹ� ����� ����
***************************************************************/
class ObjectManager
{
	SingletonHeader(ObjectManager)
private:
	typedef unordered_map<ObjectType::Enum, vector<class GameObject*>> ObjectContainer; 
	typedef unordered_map<ObjectType::Enum, vector<class GameObject*>>::iterator ObjectContainerIter;
private:
	ObjectContainer _objectContainer;
public:
	void Init();
	void Release();
	void Update();
	void Render();
public:
	void AddObject(const ObjectType::Enum type, class GameObject * pObject);
    class GameObject* FindObject(const ObjectType::Enum type, const string name);
	vector<class GameObject*> FindObjects(const ObjectType::Enum type, const string name);
	vector<class GameObject*> GetObjectList(const ObjectType::Enum type);
};
#define _ObjectManager ObjectManager::Get()
