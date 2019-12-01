//=====================================
//
//Particle3D.cpp
//機能:パーティクル3D
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "Particle3D.h"

/**************************************
コンストラクタ
***************************************/
Particle3D::Particle3D()
{
}

/**************************************
コンストラクタ
***************************************/
Particle3D::Particle3D(float life) :
	BaseParticle(life),
	BillboardObject(false)
{
}

/**************************************
コンストラクタ
***************************************/
Particle3D::Particle3D(float minLife, float maxLife) :
	BaseParticle(minLife, maxLife),
	BillboardObject(false)
{
}

/**************************************
コンストラクタ
***************************************/
Particle3D::Particle3D(float u, float v, float minLife, float maxLife) :
	BaseParticle(u, v, minLife, maxLife),
	BillboardObject(false)
{
}

/**************************************
デストラクタ
***************************************/
Particle3D::~Particle3D()
{
}

/**************************************
アクティブ判定
***************************************/
bool Particle3D::IsActive() const
{
	if (!active)
		return false;

	return _IsActive();
}

/**************************************
トランスフォーム設定処理
***************************************/
void Particle3D::SetTransform(const Transform& transform)
{
	BillboardObject::SetTransform(transform);
}

/**************************************
アクティブセット処理
***************************************/
void Particle3D::SetActive(bool state)
{
	BillboardObject::SetActive(state);
}

/**************************************
ワールド変換行列取得処理
***************************************/
D3DXMATRIX Particle3D::GetWorldMtx()
{
	return transform->GetMatrix();
}
