#pragma once
class Bullet
{
private:
	struct TagBullet
	{
		RECT rc;			//��Ʈ
		float x, y;			//�Ѿ� ��ǥ
		float fireX, fireY;	//�߻� ��ǥ
		float speed;		//�Ѿ� �ӵ�		
		float angle;		//�Ѿ� ����
	};


public:
	Bullet() {}
	~Bullet() {}

	void Init();
	void Release();
	void Update();
	void Render();

};

