//=====================================
//
//ベースパーティクル処理[BaseParticle.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "BaseParticle.h"

/**************************************
マクロ定義
***************************************/

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle() :
	uv(ParticleUV())
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(float life) :
	uv(ParticleUV()),
	lifeFrame(life)
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(float lifeMin, float lifeMax) :
	uv(ParticleUV()),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax))
{

}

/**************************************
コンストラクタ
***************************************/
BaseParticle::BaseParticle(float u, float v, float lifeMin, float lifeMax) :
	uv(ParticleUV(u, v)),
	lifeFrame(Math::RandomRange(lifeMin, lifeMax))
{
}

/**************************************
デストラクタ
***************************************/
BaseParticle::~BaseParticle()
{
}

/**************************************
アクティブ判定
***************************************/
bool BaseParticle::_IsActive() const
{
	return cntFrame <= lifeFrame;
}

/**************************************
UV座標取得
***************************************/
ParticleUV BaseParticle::GetUV() const
{
	return uv;
}