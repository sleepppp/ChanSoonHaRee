#pragma once
/***************************************************************
## SceneManager ##
***************************************************************/
class SceneManager
{
	SingletonHeader(SceneManager)
private:
	typedef unordered_map<string, class SceneBase*>::iterator SceneIter;
private:
	unordered_map<string, class SceneBase*> sceneList;
	unordered_map<string, class SceneBase*> loadingSceneList;
	class SceneBase* nowScene;

public:
	void Update();
	void Render();

	void AddScene(string name, class SceneBase* scene);
	class SceneBase* FindScene(string name);
	void LoadScene(string name,bool init = true);
};

#define _SceneManager SceneManager::Get()