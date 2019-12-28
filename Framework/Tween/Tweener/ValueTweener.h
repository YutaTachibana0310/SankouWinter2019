//=====================================
//
// ValueTweener.h
// �@�\:�l�g�D�C�[�i�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _VALUETWEENER_H_
#define _VALUETWEENER_H_

#include "../../../main.h"
#include "Tweener.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
template<class T>
class ValueTweener : public Tweener<T>
{
public:
	using Callback = std::function<void()>;

	/**************************************
	�R���X�g���N�^
	***************************************/
	ValueTweener(std::shared_ptr<T>& ref, const T& start, const T& end, int duration, EaseType type, Callback callback) :
		Tweener(ref, duration, type, callback),
		start(start),
		end(end)
	{

	}

	/**************************************
	�X�V����
	***************************************/
	void Update()
	{
		cntFrame++;

		std::shared_ptr<T> value = reference.lock();
		if (value)
		{
			float t = (float)cntFrame / duration;
			*value = Easing::EaseValue(t, start, end, easeType);
			CheckCallback();
		}
	}

protected:
	T start, end;
};

#endif