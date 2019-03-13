#pragma once
#include "GameObject.h"
class BossEffect : public GameObject
{
private:
	class Image* _bossScrollIMG;			//���� ��ũ�� �̹���
	class Animation* _bossScrollAnimation;	//���� ��ũ�� �ִϸ��̼�

	float _alpha;							//���� �� ����

public:
	BossEffect();
	~BossEffect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
};

