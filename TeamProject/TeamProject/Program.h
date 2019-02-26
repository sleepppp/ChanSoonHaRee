#pragma once
class Program
{
	class Image* image;
public:
	Program();
	~Program();

	void Init();
	void Release();
	void Update();
	void Render();
};


