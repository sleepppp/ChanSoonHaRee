#pragma once
class Bullet
{
private:
	struct TagBullet
	{
		RECT rc;				//��Ʈ
		Vector2 position;		//�Ѿ� ��ǥ
		Vector2 size;			//�Ѿ� ũ��
		Vector2 firePosition;	//�߻� ��ǥ ---> �Ÿ� ���ϱ� ����
		float speed;			//�Ѿ� �ӵ�		
		float angle;			//�Ѿ� ����
		bool isfire;				//�Ѿ� �߻� true / false
	};

private:
	vector<TagBullet> _vBullet;	//���� �Ѿ�
	typedef vector<TagBullet>::iterator vIter;	//vIter ���� �Ѿ� ���ͷ�����

	vIter _viBullet;	//���� ���ͷ����� �Ѿ� ---> for�� ������ ������

//�ʱ�ȭ�� ���� ����
private:
	int _bulletMax;				//�ִ� �Ѿ�
	float _range;				//�Ÿ�


public:
	//�ʱ�ȭ
	void Init(int bulletMax, float range);

	//������
	void Release();

	//������Ʈ
	void Update();

	//����
	void Render();

	//�߻�
	void Fire(Vector2 position, Vector2 size, float angle, float speed);

	//�����̱�
	void Move();

	//�浹 ó��
	bool Intersect(RECT rc);


	Bullet() {}
	~Bullet() {}
};

