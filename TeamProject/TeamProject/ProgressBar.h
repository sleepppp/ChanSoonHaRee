#pragma once
#include "GameObject.h"
class ProgressBar :	public GameObject
{
	enum class ProgressState 
	{
		DamageState = 0,
		DamageEndState,
		DefaultState,
		End
	};

private:
	
	//�̹��� Ŭ���� ���� - ���α׷�����
	class Image* _progressBarBackIMG;
	class Image* _progressBarFrontIMG;

	//�̹��� Ŭ���� ���� - ��Ʈ
	class Image* _heartIMG;

	//HP�� ��ġ ��ǥ X, Y
	Vector2 _hpPosition;

	//�̹��� ������
	int _imgFrameX;						//�̹��� ������ X
	int _imgFrameY;						//�̹��� ������ Y

	float _frameCount;					//������ ī��Ʈ

	//ü�¹� ����
	int _hpWidth;
	
	//���̺� HP
	float _saveHp;

	ProgressState _barState;			//���α׷��� �� ����

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

	//���α׷��� �� ����
	void ProgressBarState();
};

