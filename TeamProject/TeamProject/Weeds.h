#pragma once
#include "Enemy.h"
class Weeds :	public Enemy
{
private:
	class Image* _weeds;
	class Image* _weeds_Red;
	class Image* _weeds_White;
	class Image* _shadow;
	int _imageCount;
	float _count;
	bool _isAttack;
	int	 _attackedCount;		//�ǰݽ� �ڷ� �и��� Ÿ�̹��� ��� ���� ī��Ʈ
	float _attackTime;
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
	void Collision();
	void Move();
public:
	Weeds(Vector2 pos);
	~Weeds();
};

