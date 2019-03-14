#pragma once
#include "GameObject.h"

//�ҵ� ���� ����Ʈ
#define EFFECT_SWORDATK "swordAtkEffect"

//Ȱ ���� ����Ʈ
#define EFFECT_BOWATK "bowAtkEffect"

//���� ����Ʈ
#define EFFECT_BOOM "boomEffect"

class Effect : public GameObject
{
private:
	class Image* _effectIMG;					//����Ʈ �̹���
	class Animation* _effectAnimation;			//�ִϸ��̼�

public:
	Effect();
	~Effect();

	void Init();
	void Release();
	void Update();
	void Render();

	//�ҵ� ���� ����Ʈ
	void ComeEffect(string name, Vector2 position);

	//�������� ���� ������ static �Լ� : PlayEffect // ���ڷ� �̸��� ������ ����
	static void PlayEffect(string name, Vector2 position);
};

