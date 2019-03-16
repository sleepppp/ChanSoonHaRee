#pragma once
#include "GameObject.h"

//�ҵ� ���� ����Ʈ Ű��
#define EFFECT_SWORDATK "swordAtkEffect"
//Ȱ ���� ����Ʈ Ű��
#define EFFECT_BOWATK "bowAtkEffect"
//���� ����Ʈ Ű��
#define EFFECT_BOOM "boomEffect"
class Effect : public GameObject
{
public:
	//����Ʈ ��� ��û(��Ȱ�� ����Ʈ�� ã�� �� ����Ʈ�� ����Ѵ�)
	static void PlayEffect(const string name,const Vector2 position);
private:
	class Image* _effectIMG;					//����Ʈ �̹���
	class Animation* _effectAnimation;			//�ִϸ��̼�
public:
	Effect();
	virtual ~Effect();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	//����Ʈ ���
	void StartEffect(const string name,const Vector2 position);
};

