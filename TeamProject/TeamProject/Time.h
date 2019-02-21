/*************************************************************
## Time ##
�ð� ���� �ϴ� Ŭ���� 
*************************************************************/
#pragma once
class Time
{
	SingletonHeader(Time)
private:
	bool isHighHardware;			//���� �ϵ��� �����ϴ���
	float timeScale;				//Ÿ�̸��� ������()
	float timeElapsed;				//tick ī��Ʈ

	__int64 curTime;				//���� �ð�
	__int64 lastTime;				//���� ������ �ð�
	__int64 periodFrequency;		//���� �ϵ���� �˻�� ����

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