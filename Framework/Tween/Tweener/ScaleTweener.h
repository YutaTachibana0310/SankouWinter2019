//=====================================
//
// ScaleTweener.h
// �@�\:�X�P�[���g�D�C�[�i�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _SCALETWEENER_H_
#define _SCALETWEENER_H_

#include "../../../main.h"
#include "Tweener.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class ScaleTweener : public Tweener<Transform>
{
public:
	/**************************************
	�R���X�g���N�^
	***************************************/
	ScaleTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback) :
		Tweener<Transform>(ref, duration, type, callback),
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

		std::shared_ptr<Transform> transform = reference.lock();
		if (transform)
		{
			float t = (float)cntFrame / duration;
			transform->SetScale(Easing::EaseValue(t, start, end, easeType));
			CheckCallback();
		}
	}

private:
	D3DXVECTOR3 start, end;
};

#endif