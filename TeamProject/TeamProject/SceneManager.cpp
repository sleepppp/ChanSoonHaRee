#include "stdafx.h"
#include "SceneManager.h"

#include "SceneBase.h"

/******************************************************
## SceneManager::_instance ##
static 클래스 멤버 변수는 반드시 cpp에서 재선언 및 초기화를 해주어야 한다. 
static으로 선언하면 해당 변수는 컴파일 시에 미리 메모리가 잡힌다. 
현재는 포인터 변수이므로 주소값을 담을 4byte영역의 메모리가 컴파일과
동시에 데이터영역에 잡히게 된다. 
*******************************************************/
SceneManager* SceneManager::_instance = nullptr;
/******************************************************
## GetSingleton ## 
@@ return SceneManager* : 싱글톤 인스턴스 반환 

싱글톤 패턴 접근자 
*******************************************************/
SceneManager* SceneManager::GetSingleton()
{
	//만약 인스턴스가 생성되있지 않은 상태라면 
	if (_instance == nullptr)
	{
		//인스턴스를 새로 생성해라
		_instance = new SceneManager;
	}
	//그리고 반환 
	return _instance;
}
/******************************************************
## DeleteSingleton ##
생성한 싱글톤 삭제 
*******************************************************/
void SceneManager::DeleteSingleton()
{
	//만약 인스턴스가 존재한다면 
	if (_instance)
	{
		//삭제해라
		SafeDelete(_instance);
	}
}

/******************************************************
## SceneManager ## 
_nowScene = nullptr로 초기화해주는데
반드시 바로 할당하지 않는 포인터들은 이렇게 nullptr로 초기화 해주자 
왜냐하면 nullptr로 초기화 하지 않으면 주소값에 쓰레기값이 들어가 있기때문에
if(_nowScene != nullptr)과 같은 안정성 검사를 할 수 없다. 
*******************************************************/
SceneManager::SceneManager()
	:_nowScene(nullptr)
{
}

/******************************************************
## ~SceneManager ##
소멸자에서는 씬들의 메모리를 모두 날려주자
*******************************************************/
SceneManager::~SceneManager()
{
	//씬들이 담겨 있는 맵을 순회하면서
	SceneIter iter = _sceneList.begin();
	for (; iter != _sceneList.end(); ++iter)
	{
		//전부 삭제 
		iter->second->Release();
		SafeDelete(iter->second);
	}
	_sceneList.clear();
}


/******************************************************
## Update ## 
*******************************************************/
void SceneManager::Update()
{
	//만약 _nowScene이 nullptr값이 아니라면 Update
	if (_nowScene != nullptr)
		_nowScene->Update();
}
/******************************************************
## Render ## 
*******************************************************/
void SceneManager::Render()
{
	//만약 _nowScene값이 nullptr이 아니라면 Render
	if (_nowScene != nullptr)
		_nowScene->Render();
}
/******************************************************
## AddScene ##
@@ string name : 씬 이름 
@@ SceneBase* sceneBase : 등록할 씬 
*******************************************************/
void SceneManager::AddScene(string name, SceneBase * scene)
{
	this->_sceneList.insert(make_pair(name, scene));
}
/******************************************************
## ChangeScene ##
@@ string name: 찾을 씬 이름
*******************************************************/
void SceneManager::ChangeScene(string name)
{
	//반복자를 통해 해당 키값의 데이터를 찾는다. 
	SceneIter iter = _sceneList.find(name);
	//만약 반복자가 끝이 아니라면 찾았다는 뜻 
	if (iter != _sceneList.end())
	{
		//만약 현재 씬이 있다면 해당 씬의 Release를 호출해주자 
		if (_nowScene != nullptr)
			_nowScene->Release();
		//현재씬 = 바꿀 씬 
		_nowScene = iter->second;
		//바꾼 씬의 초기화 함수 호출
		_nowScene->Init();
	}
}
