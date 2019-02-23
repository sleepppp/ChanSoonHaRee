#include "stdafx.h"
#include "SceneManager.h"

#include "SceneBase.h"

/******************************************************
## SceneManager::_instance ##
static Ŭ���� ��� ������ �ݵ�� cpp���� �缱�� �� �ʱ�ȭ�� ���־�� �Ѵ�. 
static���� �����ϸ� �ش� ������ ������ �ÿ� �̸� �޸𸮰� ������. 
����� ������ �����̹Ƿ� �ּҰ��� ���� 4byte������ �޸𸮰� �����ϰ�
���ÿ� �����Ϳ����� ������ �ȴ�. 
*******************************************************/
SceneManager* SceneManager::_instance = nullptr;
/******************************************************
## GetSingleton ## 
@@ return SceneManager* : �̱��� �ν��Ͻ� ��ȯ 

�̱��� ���� ������ 
*******************************************************/
SceneManager* SceneManager::GetSingleton()
{
	//���� �ν��Ͻ��� ���������� ���� ���¶�� 
	if (_instance == nullptr)
	{
		//�ν��Ͻ��� ���� �����ض�
		_instance = new SceneManager;
	}
	//�׸��� ��ȯ 
	return _instance;
}
/******************************************************
## DeleteSingleton ##
������ �̱��� ���� 
*******************************************************/
void SceneManager::DeleteSingleton()
{
	//���� �ν��Ͻ��� �����Ѵٸ� 
	if (_instance)
	{
		//�����ض�
		SafeDelete(_instance);
	}
}

/******************************************************
## SceneManager ## 
_nowScene = nullptr�� �ʱ�ȭ���ִµ�
�ݵ�� �ٷ� �Ҵ����� �ʴ� �����͵��� �̷��� nullptr�� �ʱ�ȭ ������ 
�ֳ��ϸ� nullptr�� �ʱ�ȭ ���� ������ �ּҰ��� �����Ⱚ�� �� �ֱ⶧����
if(_nowScene != nullptr)�� ���� ������ �˻縦 �� �� ����. 
*******************************************************/
SceneManager::SceneManager()
	:_nowScene(nullptr)
{
}

/******************************************************
## ~SceneManager ##
�Ҹ��ڿ����� ������ �޸𸮸� ��� ��������
*******************************************************/
SceneManager::~SceneManager()
{
	//������ ��� �ִ� ���� ��ȸ�ϸ鼭
	SceneIter iter = _sceneList.begin();
	for (; iter != _sceneList.end(); ++iter)
	{
		//���� ���� 
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
	//���� _nowScene�� nullptr���� �ƴ϶�� Update
	if (_nowScene != nullptr)
		_nowScene->Update();
}
/******************************************************
## Render ## 
*******************************************************/
void SceneManager::Render()
{
	//���� _nowScene���� nullptr�� �ƴ϶�� Render
	if (_nowScene != nullptr)
		_nowScene->Render();
}
/******************************************************
## AddScene ##
@@ string name : �� �̸� 
@@ SceneBase* sceneBase : ����� �� 
*******************************************************/
void SceneManager::AddScene(string name, SceneBase * scene)
{
	this->_sceneList.insert(make_pair(name, scene));
}
/******************************************************
## ChangeScene ##
@@ string name: ã�� �� �̸�
*******************************************************/
void SceneManager::ChangeScene(string name)
{
	//�ݺ��ڸ� ���� �ش� Ű���� �����͸� ã�´�. 
	SceneIter iter = _sceneList.find(name);
	//���� �ݺ��ڰ� ���� �ƴ϶�� ã�Ҵٴ� �� 
	if (iter != _sceneList.end())
	{
		//���� ���� ���� �ִٸ� �ش� ���� Release�� ȣ�������� 
		if (_nowScene != nullptr)
			_nowScene->Release();
		//����� = �ٲ� �� 
		_nowScene = iter->second;
		//�ٲ� ���� �ʱ�ȭ �Լ� ȣ��
		_nowScene->Init();
	}
}
