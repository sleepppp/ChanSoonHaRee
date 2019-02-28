#pragma once
/*************************************************************
## Loading ##
������ �ε� Ŭ����
**************************************************************/
#include <thread>
class Loading
{
private:
	thread* loadingThread;				//�ε����� ������ 
	bool isLoadEnd;						//�ε��� �����°� 
	function<void()> loadingFunc;		//�ε��ؾ� �� �Լ�
public:
	//�����ڿ��� �ε��ؾ��� �Լ��� �־��ش�. 
	Loading(function<void()> func);
	~Loading();
	//������ �ε� ���� 
	void Start();
	//�ε��� �������� ����
	bool GetIsLoadEnd()const { return this->isLoadEnd; }
private:
	//���� ���������ư� �Լ�
	void Threading();
};

