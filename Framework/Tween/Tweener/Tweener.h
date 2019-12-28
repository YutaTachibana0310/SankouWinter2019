//=====================================
//
// Tweener.h
// �@�\:�g�D�C�[�i�[���N���X
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _TWEENER_H_
#define _TWEENER_H_

#include "../../../main.h"
#include "../../Math/Easing.h"
#include <functional>

/**************************************
�O���錾
***************************************/
class Polygon2D;

/**************************************
BaseTweener�N���X
***************************************/
class BaseTweener
{
public:
	using Callback = std::function<void()>;

	/**************************************
	�R���X�g���N�^
	***************************************/
	BaseTweener(int duration, EaseType type, Callback callback) :
		cntFrame(0),
		duration(duration),
		easeType(type),
		callback(callback)
	{
	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	virtual ~BaseTweener() {}

	/**************************************
	�I������
	***************************************/
	virtual bool IsFinished()
	{
		return cntFrame >= duration;
	}

	/**************************************
	�X�V�����@���������z�֐�
	***************************************/
	virtual void Update() = 0;

	/**************************************
	�R�[���o�b�N���s�m�F
	***************************************/
	void CheckCallback()
	{
		if (cntFrame < duration)
			return;

		if (callback == nullptr)
			return;

		callback();
	}

protected:
	int cntFrame;
	int duration;
	EaseType easeType;
	Callback callback;
};

/**************************************
Tweener�N���X
BaseTweener���p�����ăe���v���[�g��
***************************************/
template<class T>
class Tweener : public BaseTweener
{
public:
	/**************************************
	�R���X�g���N�^
	***************************************/
	Tweener(std::shared_ptr<T>& ref, int duration, EaseType type, Callback callback) :
		BaseTweener(duration, type, callback),
		reference(ref)
	{

	}

	/**************************************
	�f�X�g���N�^
	***************************************/
	virtual ~Tweener()
	{
		reference.reset();
	}

	/**************************************
	�I������
	***************************************/
	bool IsFinished() override
	{
		if (reference.expired())
			return true;

		return BaseTweener::IsFinished();
	}

protected:
	std::weak_ptr<T> reference;
};

#endif