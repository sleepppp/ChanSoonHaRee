#pragma once
#include <functional>
/**********************************************
## Animation ##
������ �̹����� �������� ������ ������ �� ��ü�� �����ϰ� �ȴ� 
Ư�� �Ѱ�츦 �����ϰ�.
*************************************************/
class Animation
{
public:
	enum class FrameDirection
	{
		Horizontal = 0,	//����(��)
		Vertical = 1,	//����(Ⱦ) 
	};
private:
	string imageKey;					//�̹��� Ű�� 
	class Image* image;					//�̹��� ������
	bool isPlay;						//�÷��� �Ұ�
	bool isLoop;						//������������
	bool isReverseX;					//�̹��� X�� ������ �ϴ���
	bool isReverseY;					//�̹��� Y�� ������ �ϴ��� 

	int currentFrameIndex;				//���� ������ ���� ���� �ε���

	float currentFrameTime;				//���� ������ ��� �ð�
	float frameUpdateTime;				//������ ī��Ʈ ���� ��ų �ð� 
	
	vector<pair<int, int>> frameList;	//������ ������ ��Ƶ� ���� 
	function<void()> func;				//������ �� ����� ���� ��ų �Լ� ������ 
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

