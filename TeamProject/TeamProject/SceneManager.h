#pragma once
class SceneManager
{
private:
	typedef map<string, class SceneBase*>::iterator SceneIter;
	map<string, class SceneBase*> _sceneList;
	class SceneBase* _nowScene;
private:
	static SceneManager* _instance;
	SceneManager();
	~SceneManager();
public:
	static SceneManager* GetSingleton();
	static void DeleteSingleton();
public:
	void Update();
	void Render();

	void AddScene(string name, class SceneBase* scene);
	void ChangeScene(string name);
};

#define _SceneManager SceneManager::GetSingleton()