#pragma once
/**********************************************************
## SceneManager ##
싱글톤 패턴의 설명을 위해 일부로 디파인싱글톤,템플릿 싱글톤을 안사용했다. 
현재 사용하고 있는 싱글톤 패턴은 다이내믹 싱글톤이다(인스턴스가 없으면 생성)
***********************************************************/
class SceneManager
{
private:
	typedef map<string, class SceneBase*>::iterator SceneIter;		//씬 담을 맵의 반복자
	map<string, class SceneBase*> _sceneList;						//씬 담을 맵
	class SceneBase* _nowScene;										//현재 실행중인 씬
private:
	static SceneManager* _instance;	//싱글톤 인스턴스 
	//생성자와 소멸자를 private로 엮어서 외부 생성을 막아버린다. 
	SceneManager();
	~SceneManager();
public:
	static SceneManager* GetSingleton();		//싱글톤 인스턴스 접근자
	static void DeleteSingleton();				//싱글톤 인스턴스 삭제 함수 
public:
	void Update();			
	void Render();

	void AddScene(string name, class SceneBase* scene);
	void ChangeScene(string name);
};

#define _SceneManager SceneManager::GetSingleton()