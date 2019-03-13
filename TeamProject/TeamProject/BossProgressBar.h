#pragma once
#include "GameObject.h"
class BossProgressBar :	public GameObject
{
enum class BossProgressState
{
	DamageState = 0,
	DamageEndState,
	DefaultState,
	End
};
private:
	class Image* _bossProgressBarImg;		//���� ���α׷��� �� �̹���
	BossProgressState _bossProgressState;	//���� ���α׷��� �� ����

	//HP�� ��ġ ��ǥ X, Y
	Vector2 _hpPosition;					//hp ��ġ ��ǥ X, Y

	//�̹��� ������
	int _imgFrameX;							//�̹��� ������ X
	int _imgFrameY;							//�̹��� ������ Y

	float _frameCount;						//������ ī��Ʈ

	int _hpWidth;							//ü�¹� ����

	float _saveHp;							//���̺� hp


public:
	BossProgressBar();
	~BossProgressBar();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;

	//������ ���
	bool SetGauge(int currentHp, int maxHp);

	//���� ���α׷��� �� ����
	void BossProgressBarState();
};

