//=====================================
//
//ベースパーティクルヘッダ[BaseParticle.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEPARTICLE_H_
#define _BASEPARTICLE_H_

#include "../../main.h"
#include "../Renderer3D/BillboardObject.h"

/**************************************
前方宣言
***************************************/

/**************************************
パーティクルのUV座標
***************************************/
class ParticleUV
{
public:
	float u, v;

	ParticleUV() :
		u(0.0f),
		v(0.0f)
	{

	}

	ParticleUV(float u, float v) :
		u(u),
		v(v)
	{

	}

	ParticleUV(const ParticleUV& rhs) :
		u(rhs.u), v(rhs.v)
	{

	}
};

/**************************************
BaseParticleクラス
※継承先でInit(), Update()を実装する
***************************************/
class BaseParticle
{
public:
	BaseParticle();
	BaseParticle(float life);
	BaseParticle(float lifeMin, float lifeMax);
	BaseParticle(float u, float v, float lifeMin, float lifeMax);
	virtual ~BaseParticle();

	virtual void Init() = 0;
	virtual void Update() = 0;

	virtual bool IsActive() const = 0;

	virtual void SetTransform(const Transform& transform) = 0;

	virtual void SetActive(bool state) = 0;

	virtual D3DXMATRIX GetWorldMtx() = 0;

	virtual ParticleUV GetUV() const;

	ParticleUV uv;

protected:
	float cntFrame;
	float lifeFrame;

	bool _IsActive() const;
};

#endif