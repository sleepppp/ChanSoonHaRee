#pragma once
/***************************************************************************************
## ObjectManager ##
��� GameObject ������ Ŭ���� 
****************************************************************************************/
class ObjectManager
{
	//��ó���� �̱��� 
	SingletonHeader(ObjectManager)
private:
	//��� ������Ʈ�� ���� ����
	vector<class GameObject*> objectList;
public:
	void Init();
	void Release();
	void Update();
	void Render();
	
	void AddObject(class GameObject* object);				//������Ʈ ��� 
	class GameObject* FindObject(string name);				//������Ʈ�� �̸����� ã�Ƽ� ��ȯ 
	vector<class GameObject*> FindObjects(string name);		//���� �̸��� ������Ʈ�� ���� ã�Ƽ� ���Ϳ� ��Ƽ� ��ȯ
	vector<class GameObject*> GetObjectList();				//��� ������Ʈ ����Ʈ ��ȯ

};

#define _ObjectManager ObjectManager::Get()