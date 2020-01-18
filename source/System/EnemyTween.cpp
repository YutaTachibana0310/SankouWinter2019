//=====================================
//
//�g�D�C�[������[EnemyTween.cpp]
//Author:GP12A332 21 ���ԗY��
//
//=====================================
#include "EnemyTween.h"
#include "../../Framework/Math/Quaternion.h"
#include "../Actor/Enemy/Base/BaseEnemy.h"
#include "../Controller/EnemyTimeController.h"

#include <algorithm>

using namespace std;
/**************************************
�}�N����`
***************************************/

/**************************************
�R���X�g���N�^
***************************************/
EnemyTween::EnemyTween()
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

/**************************************
�f�X�g���N�^
***************************************/
EnemyTween::~EnemyTween()
{
	for (auto&& tweener : tweenerContainer)
	{
		SAFE_DELETE(tweener);
	}
	tweenerContainer.clear();

	if (mInstance == this)
	{
		mInstance = NULL;
	}
}

/**************************************
�X�V����
***************************************/
void EnemyTween::Update()
{
	for (auto&& tweener : tweenerContainer)
	{
		tweener->Update();
	}

	ClearContainer();
}

/**************************************
�R���e�i�N���A����
***************************************/
void EnemyTween::ClearContainer()
{
	for (auto&& tweener : tweenerContainer)
	{
		if (!tweener->IsFinished())
			continue;

		SAFE_DELETE(tweener);
	}

	tweenerContainer.remove_if([](auto&& tweener)
	{
		return tweener == NULL;
	});
}

/**************************************
�N���A����
***************************************/
void EnemyTween::ClearAll()
{
	for (auto&& tweener : tweenerContainer)
	{
		SAFE_DELETE(tweener);
	}

	tweenerContainer.clear();
}

/**************************************
�ړ�����
***************************************/
void EnemyTween::Move(BaseEnemy& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	MoveEnemyTweener *tweener = new MoveEnemyTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
�ړ�����
***************************************/
void EnemyTween::Move(BaseEnemy& ref, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetPosition();
	Move(ref, start, end, duration, type, callback);
}

/**************************************
�X�P�[������
***************************************/
void EnemyTween::Scale(BaseEnemy& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	ScaleEnemyTweener *tweener = new ScaleEnemyTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
�X�P�[������
***************************************/
void EnemyTween::Scale(BaseEnemy& ref, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetScale();
	Scale(ref, start, end, duration, type, callback);
}

/**************************************
��]����
***************************************/
void EnemyTween::Rotate(BaseEnemy& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	RotateEnemyTweener *tweener = new RotateEnemyTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
��]����
***************************************/
void EnemyTween::Rotate(BaseEnemy& ref, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetEulerAngle();
	Rotate(ref, start, end, duration, type, callback);
}

/**************************************
��������
***************************************/
void EnemyTween::Turn(BaseEnemy & ref, const D3DXVECTOR3 & end, float duration, EaseType type, const D3DXVECTOR3& dummyAxis, std::function<void()> callback)
{
	//�n�_�ƂȂ�N�H�[�^�j�I�������߂�
	D3DXQUATERNION start = ref.transform->GetRotation();

	//�I�_�ƂȂ�N�H�[�^�j�I�������߂�
	D3DXVECTOR3 axis = Vector3::Axis(ref.transform->Forward(), end);
	float angle = Vector3::Angle(ref.transform->Forward(), end);

	//axis���[���x�N�g���i�n�_�̌����ƏI�_�̌��������s�j�̏ꍇ�̓_�~�[�A�N�V�X���g�p
	if (Vector3::Equal(axis, Vector3::Zero))
	{
		axis = dummyAxis;
	}

	D3DXQUATERNION rotQ;
	D3DXQuaternionRotationAxis(&rotQ, &axis, D3DXToRadian(angle));

	D3DXQUATERNION endQuaternion = start * rotQ;

	//��]EnemyTweener�쐬
	RotateEnemyTweener *tweener = new RotateEnemyTweener(ref.transform, start, endQuaternion, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
EnemyTweener�R���X�g���N�^
***************************************/
EnemyTween::EnemyTweener::EnemyTweener(std::shared_ptr<Transform>& ref, float duration, EaseType type, Callback callback) :
	reference(ref),
	cntFrame(0),
	duration(duration),
	type(type),
	callback(callback)
{

}

/**************************************
EnemyTweener�f�X�g���N�^
***************************************/
EnemyTween::EnemyTweener::~EnemyTweener()
{
	reference.reset();
}

/**************************************
EnemyTweener�I������
***************************************/
inline bool EnemyTween::EnemyTweener::IsFinished()
{
	if (reference.expired())
		return true;

	return cntFrame >= duration;
}

/**************************************
�R�[���o�b�N�̃`�F�b�N����
***************************************/
inline void EnemyTween::EnemyTweener::CheckCallback()
{
	if (cntFrame < duration)
		return;

	if (callback == nullptr)
		return;

	callback();
}

/**************************************
MoveEnemyTweener�R���X�g���N�^
***************************************/
EnemyTween::MoveEnemyTweener::MoveEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
MoveEnemyTweener�X�V����
***************************************/
void EnemyTween::MoveEnemyTweener::Update()
{
	cntFrame += EnemyTimeController::GetTimeScale();

	shared_ptr<Transform> transform = reference.lock();
	if (transform)
	{
		float t = cntFrame / duration;
		transform->SetPosition(Easing::EaseValue(t, start, end, type));
		CheckCallback();
	}
}

/**************************************
ScaleEnemyTweener�R���X�g���N�^
***************************************/
EnemyTween::ScaleEnemyTweener::ScaleEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
ScaleEnemyTweener�X�V����
***************************************/
void EnemyTween::ScaleEnemyTweener::Update()
{
	cntFrame += EnemyTimeController::GetTimeScale();

	shared_ptr<Transform> transform = reference.lock();
	if (transform)
	{
		float t = cntFrame / duration;
		transform->SetScale(Easing::EaseValue(t, start, end, type));
		CheckCallback();
	}
}

/**************************************
RotateEnemyTweener�R���X�g���N�^
***************************************/
EnemyTween::RotateEnemyTweener::RotateEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(Quaternion::ToQuaternion(start)),
	end(Quaternion::ToQuaternion(end))
{

}

/**************************************
RotateEnemyTweener�R���X�g���N�^
***************************************/
EnemyTween::RotateEnemyTweener::RotateEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXQUATERNION & start, const D3DXQUATERNION & end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
RotateEnemyTweener�X�V����
***************************************/
void EnemyTween::RotateEnemyTweener::Update()
{
	cntFrame += EnemyTimeController::GetTimeScale();

	shared_ptr<Transform> transform = reference.lock();
	if (transform)
	{
		float t = Easing::EaseValue(cntFrame / duration, 0.0f, 1.0f, type);
		D3DXQUATERNION quaternion;
		D3DXQuaternionSlerp(&quaternion, &start, &end, t);
		transform->SetRotation(quaternion);
		CheckCallback();
	}
}