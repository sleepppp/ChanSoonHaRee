#pragma once
class DamageFontManager
{
	SingletonHeader(DamageFontManager)
private:
	Vector2 _position;	//������ x,y
	int _damage;		//������ ��
	float _alpha;		//���� ��

	bool _isAddFont;	//������ ��Ʈ ���� bool üũ
public:
	void Init();
	void Release();
	void Update();
	void Render();

public:
	//������ ��Ʈ ���
	void ShowDamage(Vector2 position, int damage);

	//������ �̵�
	void MoveDamage();
};

#define _DamageFontManager DamageFontManager::Get()

