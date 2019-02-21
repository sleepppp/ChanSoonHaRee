#pragma once
class ObjectManager
{
	SingletonHeader(ObjectManager)
private:
	vector<class GameObject*> objectList;
public:
	void Init();
	void Release();
	void Update();
	void Render();
	
	void AddObject(class GameObject* object);
	class GameObject* FindObject(string name);
	vector<class GameObject*> FindObjects(string name);
	vector<class GameObject*> GetObjectList();

};

#define _ObjectManager ObjectManager::Get()