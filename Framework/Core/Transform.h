//=====================================
//
//トランスフォームヘッダ[Transform.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../../main.h"
#include "../Math/Quaternion.h"

#include <list>
#include <memory>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class Transform
{
public:
	//コンストラクタ
	Transform();
	Transform(const Transform&);
	virtual ~Transform();

	//演算子
	virtual Transform operator = (const Transform&);

	//移動処理
	virtual void Move(const D3DXVECTOR3& velocity);

	virtual void SetPosition(const D3DXVECTOR3& position);
	virtual void SetLocalPosition(const D3DXVECTOR3& position);

	virtual D3DXVECTOR3 GetPosition() const;
	virtual D3DXVECTOR3 GetLocalPosition() const;

	//回転処理
	virtual void Rotate(float degreeX, float degreeY, float degreeZ);
	virtual void Rotate(float degree, const D3DXVECTOR3& axis);
	virtual void Rotate(const D3DXQUATERNION& quaternion);

	virtual void SetRotation(const D3DXVECTOR3& rotation);
	virtual void SetRotation(const D3DXQUATERNION& rotation);
	virtual void SetLocalRotation(const D3DXVECTOR3& rotation);
	virtual void SetLocalRotation(const D3DXQUATERNION& rotation);

	virtual D3DXVECTOR3 GetEulerAngle() const;
	virtual D3DXVECTOR3 GetLocalEulerAngle() const;

	virtual D3DXQUATERNION GetRotation() const;
	virtual D3DXQUATERNION GetLocalRotation() const;

	//スケール処理
	virtual void Scale(const D3DXVECTOR3& delta);

	virtual void SetScale(const D3DXVECTOR3& scale);
	virtual void SetLocalScale(const D3DXVECTOR3& scale);

	virtual D3DXVECTOR3 GetScale() const;
	virtual D3DXVECTOR3 GetLocalScale() const;

	//向き
	virtual D3DXVECTOR3 Forward() const;
	virtual D3DXVECTOR3 Right() const;
	virtual D3DXVECTOR3 Up() const;

	//ワールド変換設定処理
	virtual void SetWorld() const;
	virtual D3DXMATRIX GetMatrix() const;

	//指定の位置を向かせる処理
	void LookAt(const D3DXVECTOR3& target);

	//親子設定
	virtual void AddChild(const std::shared_ptr<Transform>& transform);
	virtual void RemoveChild(Transform* transform);
	
protected:
	D3DXMATRIX mtxWorldGlobal;		//グローバル空間での変換行列
	D3DXVECTOR3 position;			//座標
	D3DXVECTOR3 scale;				//スケール
	D3DXQUATERNION rotation;		//回転

	D3DXMATRIX mtxWorldLocal;		//ローカル空間での変換行列
	D3DXVECTOR3 localPosition;		//ローカル座標
	D3DXVECTOR3 localScale;			//ローカルスケール
	D3DXQUATERNION localRotation;	//ローカル回転

	void OnUpdateParentMatrix(const D3DXMATRIX& mtxWorld);

	void MoveMatrix(const D3DXVECTOR3& offset);
	void RotateMatrix(const D3DXQUATERNION& rotate);
	void ScaleMatrix(const D3DXVECTOR3& scale);

	void _SetScale(const D3DXVECTOR3& scale);

	void UpdateChildMatrix();

	std::list<std::weak_ptr<Transform>> listChildren;
};

#endif