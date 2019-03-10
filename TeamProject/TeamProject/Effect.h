#pragma once
#include "GameObject.h"

//�ҵ� ���� ����Ʈ
#define EFFECT_SWORDATK "swordAtkEffect"

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
	void SwordAtkEffect(string name, Vector2 position);

	//�������� ���� ������ static �Լ� : PlayEffect // ���ڷ� �̸��� ������ ����
	static void PlayEffect(string name, Vector2 position);
};

