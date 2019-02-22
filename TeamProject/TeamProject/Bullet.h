#pragma once
class Bullet
{
private:
	struct TagBullet
	{
		RECT rc;				//렉트
		Vector2 position;		//총알 좌표
		Vector2 size;			//총알 크기
		Vector2 firePosition;	//발사 좌표 ---> 거리 구하기 위함
		float speed;			//총알 속도		
		float angle;			//총알 각도
		bool isfire;				//총알 발사 true / false
	};

private:
	vector<TagBullet> _vBullet;	//벡터 총알
	typedef vector<TagBullet>::iterator vIter;	//vIter 벡터 총알 이터레이터

	vIter _viBullet;	//벡터 이터레이터 총알 ---> for문 돌리기 연습용

//초기화에 담을 변수
private:
	int _bulletMax;				//최대 총알
	float _range;				//거리


public:
	//초기화
	void Init(int bulletMax, float range);

	//릴리즈
	void Release();

	//업데이트
	void Update();

	//렌더
	void Render();

	//발사
	void Fire(Vector2 position, Vector2 size, float angle, float speed);

	//움직이기
	void Move();

	//충돌 처리
	bool Intersect(RECT rc);


	Bullet() {}
	~Bullet() {}
};

