#pragma once
#include "GameObject.h"
class ProgressBar :	public GameObject
{
private:
	//�̹��� Ŭ���� ���� ���α׷�����
	class Image* _progressBarBackIMG;
	class Image* _progressBarFrontIMG;

	//HP�� ��ġ ��ǥ X, Y
	Vector2 _hpPosition;

	int _imgFrameX;
	int _imgFrameY;

	//ü�¹� ����
	int _hpWidth;
	
	//���̺� HP
	float _saveHp;

	//�׽�Ʈ��
	//���� HP
	int _testCurrentHp;

	//�ִ� HP
	int _testMaxHp;





public:
	ProgressBar();
	~ProgressBar();

	void Init();
	void Release();
	void Update();
	void Render();

	//������ ���
	bool SetGauge(int currentHp, int maxHp);
};

