//=====================================
//
// RotateTweener.h
// �@�\:��]�g�D�C�[�i�[
// Author:GP12B332 21 ���ԗY��
//
//=====================================
#ifndef _ROTATETWEENER_H_
#define _ROTATETWEENER_H_

#include "../../../main.h"
#include "Tweener.h"
#include "../../Math/Quaternion.h"

/**************************************
�O���錾
***************************************/

/**************************************
�N���X��`
***************************************/
class RotateTweener : public Tweener<Transform>
{
public:
	/**************************************
	�R���X�g���N�^
	***************************************/
	RotateTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, int duration, EaseType type, Callback callback) :
		Tweener<Transform>(ref, duration, type, callback),
		start(Quaternion::ToQuaternion(start)),
		end(Quaternion::ToQuaternion(end))
	{
	}

	/**************************************
	�R���X�g���N�^
	***************************************/
	RotateTweener(std::shared_ptr<Transform>& ref, const D3DXQUATERNION& start, const D3DXQUATERNION& end, int duration, EaseType type, Callback callback) :
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
			float t = Easing::EaseValue((float)cntFrame / duration, 0.0f, 1.0f, easeType);
			D3DXQUATERNION quaternion;
			D3DXQuaternionSlerp(&quaternion, &start, &end, t);
			transform->SetRotation(quaternion);
			CheckCallback();
		}
	}

private:
	D3DXQUATERNION start, end;
};

#endif