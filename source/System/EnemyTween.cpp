//=====================================
//
//トゥイーン処理[EnemyTween.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "EnemyTween.h"
#include "../../Framework/Math/Quaternion.h"
#include "../Actor/Enemy/Base/BaseEnemy.h"
#include "../Controller/EnemyTimeController.h"

#include <algorithm>

using namespace std;
/**************************************
マクロ定義
***************************************/

/**************************************
コンストラクタ
***************************************/
EnemyTween::EnemyTween()
{
	if (mInstance == NULL)
	{
		mInstance = this;
	}
}

/**************************************
デストラクタ
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
更新処理
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
コンテナクリア処理
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
クリア処理
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
移動処理
***************************************/
void EnemyTween::Move(BaseEnemy& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	MoveEnemyTweener *tweener = new MoveEnemyTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
移動処理
***************************************/
void EnemyTween::Move(BaseEnemy& ref, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetPosition();
	Move(ref, start, end, duration, type, callback);
}

/**************************************
スケール処理
***************************************/
void EnemyTween::Scale(BaseEnemy& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	ScaleEnemyTweener *tweener = new ScaleEnemyTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
スケール処理
***************************************/
void EnemyTween::Scale(BaseEnemy& ref, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetScale();
	Scale(ref, start, end, duration, type, callback);
}

/**************************************
回転処理
***************************************/
void EnemyTween::Rotate(BaseEnemy& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	RotateEnemyTweener *tweener = new RotateEnemyTweener(ref.transform, start, end, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
回転処理
***************************************/
void EnemyTween::Rotate(BaseEnemy& ref, const D3DXVECTOR3& end, float duration, EaseType type, std::function<void(void)> callback)
{
	D3DXVECTOR3 start = ref.transform->GetEulerAngle();
	Rotate(ref, start, end, duration, type, callback);
}

/**************************************
方向処理
***************************************/
void EnemyTween::Turn(BaseEnemy & ref, const D3DXVECTOR3 & end, float duration, EaseType type, const D3DXVECTOR3& dummyAxis, std::function<void()> callback)
{
	//始点となるクォータニオンを求める
	D3DXQUATERNION start = ref.transform->GetRotation();

	//終点となるクォータニオンを求める
	D3DXVECTOR3 axis = Vector3::Axis(ref.transform->Forward(), end);
	float angle = Vector3::Angle(ref.transform->Forward(), end);

	//axisがゼロベクトル（始点の向きと終点の向きが並行）の場合はダミーアクシスを使用
	if (Vector3::Equal(axis, Vector3::Zero))
	{
		axis = dummyAxis;
	}

	D3DXQUATERNION rotQ;
	D3DXQuaternionRotationAxis(&rotQ, &axis, D3DXToRadian(angle));

	D3DXQUATERNION endQuaternion = start * rotQ;

	//回転EnemyTweener作成
	RotateEnemyTweener *tweener = new RotateEnemyTweener(ref.transform, start, endQuaternion, duration, type, callback);
	mInstance->tweenerContainer.push_back(tweener);
}

/**************************************
EnemyTweenerコンストラクタ
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
EnemyTweenerデストラクタ
***************************************/
EnemyTween::EnemyTweener::~EnemyTweener()
{
	reference.reset();
}

/**************************************
EnemyTweener終了判定
***************************************/
inline bool EnemyTween::EnemyTweener::IsFinished()
{
	if (reference.expired())
		return true;

	return cntFrame >= duration;
}

/**************************************
コールバックのチェック判定
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
MoveEnemyTweenerコンストラクタ
***************************************/
EnemyTween::MoveEnemyTweener::MoveEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
MoveEnemyTweener更新処理
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
ScaleEnemyTweenerコンストラクタ
***************************************/
EnemyTween::ScaleEnemyTweener::ScaleEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
ScaleEnemyTweener更新処理
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
RotateEnemyTweenerコンストラクタ
***************************************/
EnemyTween::RotateEnemyTweener::RotateEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXVECTOR3& start, const D3DXVECTOR3& end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(Quaternion::ToQuaternion(start)),
	end(Quaternion::ToQuaternion(end))
{

}

/**************************************
RotateEnemyTweenerコンストラクタ
***************************************/
EnemyTween::RotateEnemyTweener::RotateEnemyTweener(std::shared_ptr<Transform>& ref, const D3DXQUATERNION & start, const D3DXQUATERNION & end, float duration, EaseType type, Callback callback) :
	EnemyTweener(ref, duration, type, callback),
	start(start),
	end(end)
{

}

/**************************************
RotateEnemyTweener更新処理
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