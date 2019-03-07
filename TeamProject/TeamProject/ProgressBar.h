#pragma once
#include "GameObject.h"
class ProgressBar :	public GameObject
{
private:
	//이미지 클래스 선언 프로그래스바
	class Image* _progressBarBackIMG;
	class Image* _progressBarFrontIMG;

	//HP바 위치 좌표 X, Y
	Vector2 _hpPosition;

	int _imgFrameX;
	int _imgFrameY;

	//체력바 길이
	int _hpWidth;
	
	//세이브 HP
	float _saveHp;

	//테스트용
	//현재 HP
	int _testCurrentHp;

	//최대 HP
	int _testMaxHp;





public:
	ProgressBar();
	~ProgressBar();

	void Init();
	void Release();
	void Update();
	void Render();

	//게이지 얻기
	bool SetGauge(int currentHp, int maxHp);
};

