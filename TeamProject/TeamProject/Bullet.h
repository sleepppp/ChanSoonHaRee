#pragma once
class Bullet
{
private:
	struct TagBullet
	{
		RECT rc;			//·ºÆ®
		float x, y;			//ÃÑ¾Ë ÁÂÇ¥
		float fireX, fireY;	//¹ß»ç ÁÂÇ¥
		float speed;		//ÃÑ¾Ë ¼Óµµ		
		float angle;		//ÃÑ¾Ë °¢µµ
	};


public:
	Bullet() {}
	~Bullet() {}

	void Init();
	void Release();
	void Update();
	void Render();

};

