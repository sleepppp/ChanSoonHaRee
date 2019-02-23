#pragma once
/**********************************************************
## SceneManager ##
�̱��� ������ ������ ���� �Ϻη� �����ν̱���,���ø� �̱����� �Ȼ���ߴ�. 
���� ����ϰ� �ִ� �̱��� ������ ���̳��� �̱����̴�(�ν��Ͻ��� ������ ����)
***********************************************************/
class SceneManager
{
private:
	typedef map<string, class SceneBase*>::iterator SceneIter;		//�� ���� ���� �ݺ���
	map<string, class SceneBase*> _sceneList;						//�� ���� ��
	class SceneBase* _nowScene;										//���� �������� ��
private:
	static SceneManager* _instance;	//�̱��� �ν��Ͻ� 
	//�����ڿ� �Ҹ��ڸ� private�� ��� �ܺ� ������ ���ƹ�����. 
	SceneManager();
	~SceneManager();
public:
	static SceneManager* GetSingleton();		//�̱��� �ν��Ͻ� ������
	static void DeleteSingleton();				//�̱��� �ν��Ͻ� ���� �Լ� 
public:
	void Update();			
	void Render();

	void AddScene(string name, class SceneBase* scene);
	void ChangeScene(string name);
};

#define _SceneManager SceneManager::GetSingleton()