#pragma once
class DamageFontManager
{
	SingletonHeader(DamageFontManager)
private:
	Vector2 _position;	//포지션 x,y
	int _damage;		//데미지 값
	float _alpha;		//알파 값

	bool _isAddFont;	//데미지 폰트 생성 bool 체크
public:
	void Init();
	void Release();
	void Update();
	void Render();

public:
	//데미지 폰트 출력
	void ShowDamage(Vector2 position, int damage);

	//데미지 이동
	void MoveDamage();
};

#define _DamageFontManager DamageFontManager::Get()

