#pragma once
class DamageFontManager
{
	SingletonHeader(DamageFontManager)

	struct DamageFont
	{
		Vector2 position;				//������
		int damage;						//������
		float speed;					//���ǵ�
		float angle;					//�ޱ�
		float alpha;					//����
		bool isAddFont;					//��Ʈ bool
	};
private:
	vector<DamageFont> _vDamageFont;	//���� ������ ��Ʈ

	bool _isAddFont;					//������ ��Ʈ ���� bool üũ
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

