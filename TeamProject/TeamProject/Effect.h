#pragma once
#include "GameObject.h"

//소드 공격 이팩트
#define EFFECT_SWORDATK "swordAtkEffect"

class Effect : public GameObject
{
private:
	class Image* _effectIMG;					//이팩트 이미지
	class Animation* _effectAnimation;			//애니메이션


public:
	Effect();
	~Effect();

	void Init();
	void Release();
	void Update();
	void Render();

	//소드 공격 이팩트
	void SwordAtkEffect(string name, Vector2 position);

	//전역에서 접근 가능한 static 함수 : PlayEffect // 인자로 이름과 포지션 받음
	static void PlayEffect(string name, Vector2 position);
};

