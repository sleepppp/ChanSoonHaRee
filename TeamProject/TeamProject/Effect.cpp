#include "stdafx.h"
#include "Effect.h"
#include "Animation.h"

// Ű �� �̸��� �������� �޴� ������
Effect::Effect()
{
	this->_name = "Effect";

	//�ҵ� ���� ����Ʈ �ִϸ��̼� new ����
	_effectAnimation = new Animation;


	this->_isActive = false;
}


Effect::~Effect()
{
	//�ִϸ��̼� �Ҹ��ڿ��� ����Ʈ
	SafeDelete(_effectAnimation);
}

void Effect::Init()
{

}

void Effect::Release()
{
	
}

void Effect::Update()
{
	//�������� �� ���� true�� ��ȯ�ϴ� UpdateFrame

	if (_effectAnimation->UpdateFrame() == true)
	{
		//�̹��� ���ֱ�
		this->SetActive(false);
	}
}

void Effect::Render()
{
	//������ ����
	//���� ������ ������x, ���� ������ ������y
	_effectIMG->SetSize(Vector2(_effectIMG->GetFrameSize(0).x, _effectIMG->GetFrameSize(0).y));

	//������ ����
	//���� ������ x,y �� ����
	_effectIMG->FrameRender(_position.x, _position.y, _effectAnimation->GetNowFrameX(), _effectAnimation->GetNowFrameY(), Pivot::CENTER, true);
}

void Effect::StartEffect(const string name,const Vector2 position)
{
	if (this->_isActive == false) 
	{
		//������ Ű ���� �̹��� �̸����� �޾ƿ�
		_effectIMG = _ImageManager->FindImage(name);

		this->_position = position;
		
		//���� ������ x,y�� �� ������ x,y
		_effectAnimation->SetStartEndFrame(0, 0, _effectIMG->GetMaxFrameX() - 1, 0, false);
		//���� ����
		_effectAnimation->SetIsLoop(true);
		//������ ���� �ð�
		_effectAnimation->SetFrameUpdateTime(0.1f);

		//�ִϸ��̼� ����
		_effectAnimation->Play();
		
		//��Ƽ�� true
		this->SetActive(true);
	}

}

void Effect::PlayEffect(const string name,const Vector2 position)
{
	//���� �����ͷ� ���� ���
	const vector<GameObject*>* _effectTest;
	//������Ʈ Ÿ�� ����Ʈ ã�Ƽ� �����ͷ� ���� ��������
	_effectTest = _ObjectManager->GetObjectListPointer(ObjectType::Effect);

	//�����ŭ ������
	for (UINT i = 0; i < _effectTest->size(); ++i)
	{
		//��Ƽ�갡 false�̸�
		if (_effectTest->at(i)->GetActive() == false)
		{
			//static_cast<Effect*>(_effectTest->at(i));
			if (dynamic_cast<Effect*>(_effectTest->at(i)) != nullptr)
			{
				dynamic_cast<Effect*>(_effectTest->at(i))->StartEffect(name, position);
				break;
			}

		}

	}

}
