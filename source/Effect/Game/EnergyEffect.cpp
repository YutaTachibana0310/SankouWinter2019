//=====================================
//
//EnergyEffect.cpp
//機能:エナジーエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnergyEffect.h"

namespace Effect::Game 
{
	/**************************************
	staticメンバ
	***************************************/
	const float EnergyEffect::LifeFrame = 60.0f;

	/**************************************
	EnergyEffectControllerコンストラクタ
	***************************************/
	EnergyEffectController::EnergyEffectController() :
		BaseParticleController(Particle_2D)
	{
		const D3DXVECTOR2 Size = { 21.5f, -21.5f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/PlayerTrail.png");

		const unsigned MaxEmitter = 128;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnergyEffectEmitter();
		}
	}

	/**************************************
	EnergyEffectコンストラクタ
	***************************************/
	EnergyEffect::EnergyEffect() :
		Particle2D(LifeFrame),
		velocity(Vector3::Zero)
	{

	}

	/**************************************
	EnergyEffect初期化処理
	***************************************/
	void EnergyEffect::Init()
	{
		cntFrame = 0.0f;
		active = true;
	}

	/**************************************
	EnergyEffect更新処理
	***************************************/
	void EnergyEffect::Update()
	{
		if (!IsActive())
			return;

		D3DXVECTOR3 acceleration = Vector3::Zero;
		float t = 1.0f - cntFrame / lifeFrame;

		const D3DXVECTOR3 TargetPosition = { 900.0f, 80.0f, 0.0f };
		D3DXVECTOR3 diff = TargetPosition - transform->GetPosition();

		acceleration = (diff - velocity * t) * 2.0f / (t * t);

		cntFrame += FixedTime::GetTimeScale();

		velocity += acceleration / 60.0f * FixedTime::GetTimeScale();
		transform->Move(velocity / 60.0f * FixedTime::GetTimeScale());
	}

	/**************************************
	方向設定処理
	***************************************/
	void EnergyEffect::SetDirection(const D3DXVECTOR3 & direction)
	{
		velocity = direction * 1500.0f;
	}

	/**************************************
	EnergyEffectEmitterコンストラクタ
	***************************************/
	EnergyEffectEmitter::EnergyEffectEmitter() :
		BaseEmitter(8, 2.0f)
	{
		particleContainer.resize(8, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnergyEffect();
		}
	}

	/**************************************
	EnergyEffectEmitter放出処理
	***************************************/
	bool EnergyEffectEmitter::Emit()
	{
		if (!enableEmit)
			return true;

		if (cntFrame < prevEmitTime)
			return true;

		prevEmitTime = ceilf(cntFrame);

		D3DXVECTOR3 direction = Vector3::Up;
		D3DXMATRIX mtxRot;
		D3DXMatrixRotationAxis(&mtxRot, &Vector3::Forward, D3DXToRadian(360.0f / 8.0f));

		for (auto&& particle : particleContainer)
		{
			if (particle->IsActive())
				continue;

			particle->SetTransform(*transform);
			particle->Init();
			dynamic_cast<EnergyEffect*>(particle)->SetDirection(direction);

			D3DXVec3TransformCoord(&direction, &direction, &mtxRot);
		}

		return true;
	}
}