#pragma once
#include <functional>
/**********************************************
## Animation ##
앞으로 이미지의 프레임을 돌리는 과정은 이 객체에 일임하게 된다 
특수 한경우를 제외하고.
*************************************************/
class Animation
{
public:
	enum class FrameDirection
	{
		Horizontal = 0,	//가로(종)
		Vertical = 1,	//세로(횡) 
	};
private:
	string imageKey;					//이미지 키값 
	class Image* image;					//이미지 포인터
	bool isPlay;						//플레이 불값
	bool isLoop;						//루프돌리느냐
	bool isReverseX;					//이미지 X를 리버스 하느냐
	bool isReverseY;					//이미지 Y를 리버스 하느냐 

	int currentFrameIndex;				//현재 프레임 정보 벡터 인덱스

	float currentFrameTime;				//현재 프레임 재는 시간
	float frameUpdateTime;				//프레임 카운트 증가 시킬 시간 
	
	vector<pair<int, int>> frameList;	//프레임 데이터 담아둔 벡터 
	function<void()> func;				//프레임 다 감기면 실행 시킬 함수 포인터 
public:
	Animation();
	~Animation();

	void UpdateFrame();
	void Render(RECT rc);

	void Start();
	void Stop();
	void Pause();

	void SetVectorFrame(vector<pair<int, int>> playFrame);
	void SetStartEndFrame(int startX, int startY, int endX, int endY,
		bool reverse, FrameDirection direction = FrameDirection::Horizontal);

public:
	void SetCallbackFunc(function<void()> func);
	void SetImage(class Image* image);
	void SetImage(string name);
	void SetIsReverseX(bool b) { this->isReverseX = b; }
	void SetIsReverseY(bool b) { this->isReverseY = b; }
	void SetIsLoop(bool b) { this->isLoop = b; }
	void SetFrameUpdateTime(float frameRate) { this->frameUpdateTime = frameRate; }
public:
	float GetFrameUpdateTime()const { return this->frameUpdateTime; }
	bool GetIsReverseX()const { return this->isReverseX; }
	bool GetIsReverseY()const { return this->isReverseY; }
	bool getIsLoop()const { return this->isLoop; }
	pair<int, int> GetNowFrameData()const;
	int GetNowFrameX()const;
	int GetNowFrameY()const;
};

