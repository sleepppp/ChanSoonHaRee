#pragma once
#include "Enemy.h"
class Slime :
	public Enemy
{
	//�ɲ��̷� ���ƴٴϴٰ� �÷��̾ �߰��ϸ� ��¦�پ ��Ÿ� �̵��� �ϰ� �����ϴ°Ŷ� 
	//��¦�پ �÷��̾�� �پ �÷��̾ �����ð����� ���ΰ� �׻��̽ð����� ��Ʈ�������� �ִ� ��.
public:
	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
public:
	Slime();
	~Slime();
};

