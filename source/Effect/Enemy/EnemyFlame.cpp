//=====================================
//
// EnemyFlame.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyFlame.h"
#include "../../../Framework/Math/Easing.h"
#include "../../Controller/EnemyTimeController.h"

namespace Effect::Game
{
	/**************************************
	グローバル変数
	***************************************/
	const float EnemyFlame::MinSpeed = 0.15f;
	const float EnemyFlame::MaxSpeed = 0.3f;
	const D3DXVECTOR3 EnemyFlame::RangeOffset = { 1.0f, 1.0f, 1.0f };

	/**************************************
	EnemyFlameControllerコンストラクタ
	***************************************/
	EnemyFlameController::EnemyFlameController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 2.0f, 2.0f };
		const D3DXVECTOR2 Split = { 3.0f, 3.0f };
		MakeUnitBuffer(Size, Split);

		LoadTexture("data/TEXTURE/Particle/EnemyFlame.png");

		const unsigned MaxEmitter = 64;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnemyFlameEmitter();
		}
	}


	/**************************************
	EnemyFlameコンストラクタ
	***************************************/
	EnemyFlame::EnemyFlame() :
		AnimationParticle3D(3.0f, 3.0f, 20.0f, 30.0f)
	{
		moveDir = Vector3::Random();
	}

	/**************************************
	EnemyFlame初期化処理
	***************************************/
	void EnemyFlame::Init()
	{
		active = true;
		cntFrame = 0.0f;

		initSpeed = Math::RandomRange(MinSpeed, MaxSpeed);

		transform->Rotate(Math::RandomRange(0.0f, 360.0f), Vector3::Forward);

		transform->SetScale(Vector3::One * Math::RandomRange(0.8f, 1.2f));

		transform->Move(Vector3::Random() * Math::RandomRange(-2.0f, 2.0f));
	}

	/**************************************
	EnemyFlame更新処理
	***************************************/
	void EnemyFlame::Update()
	{
		if (!IsActive())
			return;

		cntFrame += EnemyTimeController::GetTimeScale();

		float t = cntFrame / lifeFrame;

		float speed = Easing::EaseValue(t, initSpeed, 0.0f, EaseType::OutCubic);
		transform->Move(speed * moveDir * EnemyTimeController::GetTimeScale());

		Animation(t);
	}

	/**************************************
	EnemyFlameEmitterコンストラクタ
	***************************************/
	EnemyFlameEmitter::EnemyFlameEmitter() :
		Enemy::EnemyParticleEmitter(20, 4.0f)
	{
		particleContainer.resize(64, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnemyFlame();
		}
	}
}
