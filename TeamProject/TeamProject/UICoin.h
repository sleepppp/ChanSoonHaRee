#pragma once
#include "GameObject.h"
class UICoin : public GameObject
{
private:
	class Image* _coinIMG;		//���� �̹���

public:
	UICoin();
	~UICoin();

	void Init()override;
	void Release()override;
	void Update()override;
	void Render()override;
};

