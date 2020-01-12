//=====================================
//
//トランスフォーム処理[Transform.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "Transform.h"

/**************************************
コンストラクタ
***************************************/
Transform::Transform() :
	position(Vector3::Zero),
	rotation(Quaternion::Identity),
	scale(Vector3::One),
	localPosition(Vector3::Zero),
	localRotation(Quaternion::Identity),
	localScale(Vector3::One)
{
	D3DXMatrixIdentity(&mtxWorldGlobal);
	D3DXMatrixIdentity(&mtxWorldLocal);
}

/**************************************
コンストラクタ
***************************************/
Transform::Transform(const Transform& src) :
	position(src.position),
	rotation(src.rotation),
	scale(src.scale),
	localPosition(Vector3::Zero),
	localRotation(Quaternion::Identity),
	localScale(Vector3::One)
{
	D3DXMatrixIdentity(&mtxWorldGlobal);
	D3DXMatrixIdentity(&mtxWorldLocal);
}

/**************************************
デストラクタ
***************************************/
Transform::~Transform()
{
	for (auto&& wptr : listChildren)
	{
		wptr.reset();
	}
	listChildren.clear();
}

/**************************************
代入演算子
***************************************/
Transform Transform::operator=(const Transform& src)
{
	this->mtxWorldGlobal = src.mtxWorldGlobal;
	this->position = src.position;
	this->rotation = src.rotation;
	this->scale = src.scale;

	this->mtxWorldLocal = src.mtxWorldLocal;
	this->localPosition = src.localPosition;
	this->localRotation = src.localRotation;
	this->localScale = src.localScale;

	return *this;
}

/**************************************
移動処理
***************************************/
void Transform::Move(const D3DXVECTOR3& velocity)
{
	position += velocity;
	localPosition += velocity;

	MoveMatrix(velocity);
}

/**************************************
座標設定
***************************************/
void Transform::SetPosition(const D3DXVECTOR3& position)
{
	D3DXVECTOR3 offset = position - this->position;
	Move(offset);
}

/**************************************
ローカル座標設定
***************************************/
void Transform::SetLocalPosition(const D3DXVECTOR3& position)
{
	D3DXVECTOR3 offset = position - localPosition;
	Move(offset);
}

/**************************************
座標取得
***************************************/
D3DXVECTOR3 Transform::GetPosition() const
{
	return position;
}

/**************************************
ローカル座標取得
***************************************/
D3DXVECTOR3 Transform::GetLocalPosition() const
{
	return localPosition;
}

/**************************************
回転処理
***************************************/
void Transform::Rotate(float degX, float degY, float degZ)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationYawPitchRoll(&q, D3DXToRadian(degY), D3DXToRadian(degX), D3DXToRadian(degZ));
	Rotate(q);
}

/***************************************
回転処理
***************************************/
void Transform::Rotate(float deg, const D3DXVECTOR3& axis)
{
	D3DXQUATERNION q;
	D3DXQuaternionRotationAxis(&q, &axis, D3DXToRadian(deg));
	Rotate(q);
}

/***************************************
回転処理
***************************************/
void Transform::Rotate(const D3DXQUATERNION& quaternion)
{
	D3DXQuaternionMultiply(&rotation, &rotation, &quaternion);
	D3DXQuaternionNormalize(&rotation, &rotation);

	D3DXQuaternionMultiply(&localRotation, &localRotation, &quaternion);
	D3DXQuaternionNormalize(&localRotation, &localRotation);

	RotateMatrix(quaternion);
}

/**************************************
グローバル回転処理
***************************************/
void Transform::SetRotation(const D3DXVECTOR3& rotation)
{
	D3DXQUATERNION inverseRot;
	D3DXQuaternionInverse(&inverseRot, &this->rotation);

	D3DXQUATERNION target = Quaternion::ToQuaternion(rotation);

	D3DXQUATERNION offset;
	D3DXQuaternionMultiply(&offset, &inverseRot, &target);

	Rotate(offset);
}

/**************************************
グローバル回転設定処理
***************************************/
void Transform::SetRotation(const D3DXQUATERNION& rotation)
{
	D3DXQUATERNION inverseRot;
	D3DXQuaternionInverse(&inverseRot, &this->rotation);

	D3DXQUATERNION offset;
	D3DXQuaternionMultiply(&offset, &inverseRot, &rotation);

	Rotate(offset);
}

/**************************************
ローカル回転設定処理
***************************************/
void Transform::SetLocalRotation(const D3DXVECTOR3& rotation)
{
	D3DXQUATERNION inverseRot;
	D3DXQuaternionInverse(&inverseRot, &this->localRotation);

	D3DXQUATERNION target = Quaternion::ToQuaternion(rotation);

	D3DXQUATERNION offset;
	D3DXQuaternionMultiply(&offset, &inverseRot, &target);

	Rotate(offset);
}

/**************************************
ローカル回転設定処理
***************************************/
void Transform::SetLocalRotation(const D3DXQUATERNION& rotation)
{
	D3DXQUATERNION inverseRot;
	D3DXQuaternionInverse(&inverseRot, &this->localRotation);

	D3DXQUATERNION offset;
	D3DXQuaternionMultiply(&offset, &inverseRot, &rotation);

	Rotate(offset);
}

/***************************************
オイラー角取得処理
***************************************/
D3DXVECTOR3 Transform::GetEulerAngle() const
{
	return Quaternion::ToEuler(rotation);
}

/***************************************
オイラー角取得処理
***************************************/
D3DXVECTOR3 Transform::GetLocalEulerAngle() const
{
	return Quaternion::ToEuler(localRotation);
}

/**************************************
回転取得処理
***************************************/
D3DXQUATERNION Transform::GetRotation() const
{
	return rotation;
}

/**************************************
回転取得処理
***************************************/
D3DXQUATERNION Transform::GetLocalRotation() const
{
	return localRotation;
}

/**************************************
スケール処理
***************************************/
void Transform::Scale(const D3DXVECTOR3& delta)
{
	scale.x *= delta.x;
	scale.y *= delta.y;
	scale.z *= delta.z;

	localScale.x *= delta.x;
	localScale.y *= delta.y;
	localScale.z *= delta.z;

	ScaleMatrix(delta);
}

/**************************************
グローバルスケール設定
***************************************/
void Transform::SetScale(const D3DXVECTOR3& scale)
{
	if (Math::Approximately(this->scale.x, 0.0f) || Math::Approximately(this->scale.y, 0.0f) || Math::Approximately(this->scale.z, 0.0f))
	{
		_SetScale(scale);
	}
	else
	{
		D3DXVECTOR3 delta = { scale.x / this->scale.x, scale.y / this->scale.y, scale.z / this->scale.z };
		Scale(delta);
	}
}

/**************************************
ローカルスケール設定
***************************************/
void Transform::SetLocalScale(const D3DXVECTOR3& scale)
{
	if (Math::Approximately(this->localScale.x, 0.0f) || Math::Approximately(this->localScale.y, 0.0f) || Math::Approximately(this->localScale.z, 0.0f))
	{
		_SetScale(scale);
	}
	else
	{
		D3DXVECTOR3 delta = { scale.x / this->localScale.x, scale.y / this->localScale.y, scale.z / this->localScale.z };
		Scale(delta);
	}
}

/**************************************
スケール取得
***************************************/
D3DXVECTOR3 Transform::GetScale() const
{
	return scale;
}

/**************************************
ローカルスケール取得
***************************************/
D3DXVECTOR3 Transform::GetLocalScale() const
{
	return localScale;
}

/**************************************
ワールド変換処理
***************************************/
void Transform::SetWorld() const
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorldGlobal);
}

/**************************************
前方計算処理
***************************************/
D3DXVECTOR3 Transform::Forward() const
{
	D3DXVECTOR3 forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &this->rotation);
	D3DXVec3TransformCoord(&forward, &forward, &rotation);

	return forward;
}

/**************************************
右方計算処理
***************************************/
D3DXVECTOR3 Transform::Right() const
{
	D3DXVECTOR3 right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &this->rotation);
	D3DXVec3TransformCoord(&right, &right, &rotation);

	return right;
}

/**************************************
上方計算処理
***************************************/
D3DXVECTOR3 Transform::Up() const
{
	D3DXVECTOR3 up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	D3DXMATRIX rotation;

	D3DXMatrixRotationQuaternion(&rotation, &this->rotation);
	D3DXVec3TransformCoord(&up, &up, &rotation);

	return up;
}

/**************************************
ワールド行列取得処理
***************************************/
D3DXMATRIX Transform::GetMatrix() const
{
	return mtxWorldGlobal;
}

/**************************************
指定の座標を向かせる処理
***************************************/
void Transform::LookAt(const D3DXVECTOR3& target)
{
	D3DXVECTOR3 z = (target - position);
	D3DXVec3Normalize(&z, &z);

	D3DXVECTOR3 x;
	D3DXVec3Cross(&x, &Vector3::Up, &z);
	D3DXVec3Normalize(&x, &x);

	D3DXVECTOR3 y;
	D3DXVec3Cross(&y, &z, &x);
	D3DXVec3Normalize(&y, &y);

	D3DXMATRIX m;
	D3DXMatrixIdentity(&m);
	m._11 = x.x; m._12 = y.x; m._13 = z.x;
	m._21 = x.y; m._22 = y.y; m._23 = z.y;
	m._31 = x.z; m._32 = y.z; m._33 = z.z;

	D3DXQUATERNION rot = Quaternion::GetRotation(m);
	SetRotation(rot);
}

/**************************************
子追加
***************************************/
void Transform::AddChild(const std::shared_ptr<Transform>& transform)
{
	listChildren.push_back(transform);
}

/**************************************
子離脱
***************************************/
void Transform::RemoveChild(Transform* transform)
{
	for (auto&& child : listChildren)
	{
		auto sptr = child.lock();

		if (!sptr)
			continue;

		if (sptr.get() != transform)
			continue;

		//自身の子リストから削除
		child.reset();
	}

	listChildren.remove_if([](auto wptr)
		{
			return wptr.expired();
		});
}

/**************************************
グローバル空間でのワールド変換行列更新処理
***************************************/
void Transform::OnUpdateParentMatrix(const D3DXMATRIX& mtxWorld)
{
	D3DXMatrixMultiply(&mtxWorldGlobal, &mtxWorldLocal, &mtxWorld);

	position.x = mtxWorldGlobal._41;
	position.y = mtxWorldGlobal._42;
	position.z = mtxWorldGlobal._43;

	D3DXVECTOR3 scaleX = { mtxWorldGlobal._11, mtxWorldGlobal._12, mtxWorldGlobal._13 };
	D3DXVECTOR3 scaleY = { mtxWorldGlobal._21, mtxWorldGlobal._22, mtxWorldGlobal._23 };
	D3DXVECTOR3 scaleZ = { mtxWorldGlobal._31, mtxWorldGlobal._32, mtxWorldGlobal._33 };

	scale.x = D3DXVec3Length(&scaleX);
	scale.y = D3DXVec3Length(&scaleY);
	scale.z = D3DXVec3Length(&scaleZ);

	D3DXQuaternionRotationMatrix(&rotation, &mtxWorldGlobal);
	D3DXQuaternionNormalize(&rotation, &rotation);

	UpdateChildMatrix();
}

/**************************************
内部移動処理
***************************************/
void Transform::MoveMatrix(const D3DXVECTOR3& offset)
{
	mtxWorldGlobal._41 += offset.x;
	mtxWorldGlobal._42 += offset.y;
	mtxWorldGlobal._43 += offset.z;

	mtxWorldLocal._41 += offset.x;
	mtxWorldLocal._42 += offset.y;
	mtxWorldLocal._43 += offset.z;

	UpdateChildMatrix();
}

/**************************************
内部回転処理
***************************************/
void Transform::RotateMatrix(const D3DXQUATERNION& rotate)
{
	D3DXMatrixRotationQuaternion(&mtxWorldGlobal, &rotation);

	mtxWorldGlobal._11 *= scale.x;
	mtxWorldGlobal._12 *= scale.x;
	mtxWorldGlobal._13 *= scale.x;

	mtxWorldGlobal._21 *= scale.y;
	mtxWorldGlobal._22 *= scale.y;
	mtxWorldGlobal._23 *= scale.y;

	mtxWorldGlobal._31 *= scale.z;
	mtxWorldGlobal._32 *= scale.z;
	mtxWorldGlobal._33 *= scale.z;

	mtxWorldGlobal._41 = position.x;
	mtxWorldGlobal._42 = position.y;
	mtxWorldGlobal._43 = position.z;

	D3DXMatrixRotationQuaternion(&mtxWorldLocal, &localRotation);

	mtxWorldLocal._11 *= localScale.x;
	mtxWorldLocal._12 *= localScale.x;
	mtxWorldLocal._13 *= localScale.x;

	mtxWorldLocal._21 *= localScale.y;
	mtxWorldLocal._22 *= localScale.y;
	mtxWorldLocal._23 *= localScale.y;

	mtxWorldLocal._31 *= localScale.z;
	mtxWorldLocal._32 *= localScale.z;
	mtxWorldLocal._33 *= localScale.z;

	mtxWorldLocal._41 = localPosition.x;
	mtxWorldLocal._42 = localPosition.y;
	mtxWorldLocal._43 = localPosition.z;

	UpdateChildMatrix();
}

/**************************************
内部スケール処理
***************************************/
void Transform::ScaleMatrix(const D3DXVECTOR3& scale)
{
	mtxWorldGlobal._11 *= scale.x;
	mtxWorldGlobal._12 *= scale.x;
	mtxWorldGlobal._13 *= scale.x;

	mtxWorldGlobal._21 *= scale.y;
	mtxWorldGlobal._22 *= scale.y;
	mtxWorldGlobal._23 *= scale.y;

	mtxWorldGlobal._31 *= scale.z;
	mtxWorldGlobal._32 *= scale.z;
	mtxWorldGlobal._33 *= scale.z;

	mtxWorldLocal._11 *= scale.x;
	mtxWorldLocal._12 *= scale.x;
	mtxWorldLocal._13 *= scale.x;

	mtxWorldLocal._21 *= scale.y;
	mtxWorldLocal._22 *= scale.y;
	mtxWorldLocal._23 *= scale.y;

	mtxWorldLocal._31 *= scale.z;
	mtxWorldLocal._32 *= scale.z;
	mtxWorldLocal._33 *= scale.z;

	UpdateChildMatrix();
}

/**************************************
スケール設定内部処理
***************************************/
void Transform::_SetScale(const D3DXVECTOR3& scale)
{
	this->scale = scale;

	D3DXMatrixRotationQuaternion(&mtxWorldGlobal, &rotation);

	mtxWorldGlobal._11 *= scale.x;
	mtxWorldGlobal._12 *= scale.x;
	mtxWorldGlobal._13 *= scale.x;

	mtxWorldGlobal._21 *= scale.y;
	mtxWorldGlobal._22 *= scale.y;
	mtxWorldGlobal._23 *= scale.y;

	mtxWorldGlobal._31 *= scale.z;
	mtxWorldGlobal._32 *= scale.z;
	mtxWorldGlobal._33 *= scale.z;

	mtxWorldGlobal._41 = position.x;
	mtxWorldGlobal._42 = position.y;
	mtxWorldGlobal._43 = position.z;

	D3DXMatrixRotationQuaternion(&mtxWorldLocal, &localRotation);

	mtxWorldLocal._11 *= scale.x;
	mtxWorldLocal._12 *= scale.x;
	mtxWorldLocal._13 *= scale.x;

	mtxWorldLocal._21 *= scale.y;
	mtxWorldLocal._22 *= scale.y;
	mtxWorldLocal._23 *= scale.y;

	mtxWorldLocal._31 *= scale.z;
	mtxWorldLocal._32 *= scale.z;
	mtxWorldLocal._33 *= scale.z;

	mtxWorldLocal._41 = localPosition.x;
	mtxWorldLocal._42 = localPosition.y;
	mtxWorldLocal._43 = localPosition.z;

}

/**************************************
子のワールド変換行列更新処理
***************************************/
void Transform::UpdateChildMatrix()
{
	listChildren.remove_if([](auto wptr)
		{
			return wptr.expired();
		});

	for (auto&& child : listChildren)
	{
		auto sptr = child.lock();

		sptr->OnUpdateParentMatrix(mtxWorldGlobal);
	}
}

