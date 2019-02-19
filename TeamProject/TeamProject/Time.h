#pragma once
class Time
{
	SingletonHeader(Time)
private:
	bool isHighHardware;	//고성능 하드웨어를 지원하느냐
	float timeScale;		//타이머의 스케일()
	float timeElapsed;		//tick 카운트

	__int64 curTime;
	__int64 lastTime;
	__int64 periodFrequency;

	unsigned long frameRate;
	unsigned long fpsFrameCount;
	float fpsTimeElapsed;
	float worldTime;
private:
	void Tick(float lockFPS = 60.0f);
public:
	void Init();
	void Update();
	void Render();

	unsigned long GetFrameRate() const { return frameRate; }
	float DeltaTime()const { return this->timeElapsed; }
	float GetWorldTime()const { return this->worldTime; }
	float GetTimeScale()const { return this->timeScale; }
	void SetTimeScale(float scale) { this->timeScale = scale; }
	void AddTimeScale(float fValue) { this->timeScale += fValue; }
	void MinusTimeScale(float fValue) { this->timeScale -= fValue; }
};

#define _Time Time::Get()