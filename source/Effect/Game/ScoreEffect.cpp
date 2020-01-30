//=====================================
//
//ScoreEffect.cpp
//機能:エナジーエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "ScoreEffect.h"
#include "../../System/GameScore.h"

namespace Effect::Game
{
	/**************************************
	staticメンバ
	***************************************/
	const float ScoreEffect::LifeFrame = 60.0f;

	/**************************************
	ScoreEffectControllerコンストラクタ
	***************************************/
	ScoreEffectController::ScoreEffectController() :
		BaseParticleController(Particle_2D)
	{
		const D3DXVECTOR2 Size = { 21.5f, -21.5f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/ScoreEffect.png");

		const unsigned MaxEmitter = 128;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new ScoreEffectEmitter();
		}
	}

	/**************************************
	ScoreEffectControllerエミッターセット処理
	***************************************/
	void ScoreEffectController::SetEmitter(const D3DXVECTOR3 & position, int point)
	{
		auto emitter = find_if(emitterContainer.begin(), emitterContainer.end(), [](BaseEmitter* emitter)
		{
			return !emitter->IsActive();
		});

		if (emitter == emitterContainer.end())
			return;

		auto ptr = dynamic_cast<ScoreEffectEmitter*>(*emitter);
		ptr->SetPosition(position);
		ptr->Init(nullptr);
		ptr->SetScore(point);

		return;
	}

	/**************************************
	ScoreEffectコンストラクタ
	***************************************/
	ScoreEffect::ScoreEffect() :
		Particle2D(LifeFrame),
		velocity(Vector3::Zero)
	{

	}

	/**************************************
	ScoreEffectデストラクタ
	***************************************/
	ScoreEffect::~ScoreEffect()
	{
	}

	/**************************************
	ScoreEffect初期化処理
	***************************************/
	void ScoreEffect::Init()
	{
		cntFrame = 0.0f;
		active = true;
	}

	/**************************************
	ScoreEffect更新処理
	***************************************/
	void ScoreEffect::Update()
	{
		if (!IsActive())
			return;

		D3DXVECTOR3 acceleration = Vector3::Zero;
		float t = 1.0f - cntFrame / lifeFrame;

		const D3DXVECTOR3 TargetPosition = { 1850.0f, 80.0f, 0.0f };
		D3DXVECTOR3 diff = TargetPosition - transform->GetPosition();

		acceleration = (diff - velocity * t) * 2.0f / (t * t);

		cntFrame += FixedTime::GetTimeScale();

		velocity += acceleration / 60.0f * FixedTime::GetTimeScale();
		transform->Move(velocity / 60.0f * FixedTime::GetTimeScale());

		if (cntFrame >= LifeFrame)
		{
			GameScore::Instance()->AddScore(point);
		}
	}

	/**************************************
	方向設定処理
	***************************************/
	void ScoreEffect::SetDirection(const D3DXVECTOR3 & direction)
	{
		velocity = direction * 1500.0f;
	}

	/**************************************
	エナジー量設定処理
	***************************************/
	void ScoreEffect::SetScore(int point)
	{
		this->point = point;
	}

	/**************************************
	ScoreEffectEmitterコンストラクタ
	***************************************/
	ScoreEffectEmitter::ScoreEffectEmitter() :
		BaseEmitter(8, 2.0f)
	{
		particleContainer.resize(8, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new ScoreEffect();
		}
	}

	/**************************************
	ScoreEffectEmitter放出処理
	***************************************/
	bool ScoreEffectEmitter::Emit()
	{
		if (!enableEmit)
			return true;

		if (cntFrame < prevEmitTime)
			return true;

		prevEmitTime = ceilf(cntFrame);

		D3DXVECTOR3 direction = Vector3::Up;
		D3DXMATRIX mtxRot;
		D3DXMatrixRotationAxis(&mtxRot, &Vector3::Forward, D3DXToRadian(360.0f / 16.0f));
		D3DXVec3TransformCoord(&direction, &direction, &mtxRot);

		D3DXMatrixRotationAxis(&mtxRot, &Vector3::Forward, D3DXToRadian(360.0f / 8.0f));
		for (auto&& particle : particleContainer)
		{
			if (particle->IsActive())
				continue;

			particle->SetTransform(*transform);
			particle->Init();

			ScoreEffect *effect = dynamic_cast<ScoreEffect*>(particle);
			effect->SetDirection(direction);
			effect->SetScore(point / 8);

			D3DXVec3TransformCoord(&direction, &direction, &mtxRot);
		}

		return true;
	}

	/**************************************
	エナジー量設定処理
	***************************************/
	void ScoreEffectEmitter::SetScore(int point)
	{
		this->point = point;
	}
}