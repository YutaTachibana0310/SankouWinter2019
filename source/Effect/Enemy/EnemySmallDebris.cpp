//=====================================
//
// EnemySmallDebris.cpp
// 機能:
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemySmallDebris.h"
#include "../../Controller/EnemyTimeController.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	グローバル変数
	***************************************/
	const float EnemySmallDebris::MaxSpeed = 0.05f;
	const float EnemySmallDebris::MinSpeed = 0.01f;

	/**************************************
	EnemySmallDebrisControllerコンストラクタ
	***************************************/
	EnemySmallDebrisController::EnemySmallDebrisController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 0.75f, 0.75f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/EnemyDebris.png");

		const unsigned MaxEmitter = 64;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnemySmallDebirsEmitter();
		}
	}

	/**************************************
	EnemySmallDebrisコンストラクタ
	***************************************/
	EnemySmallDebris::EnemySmallDebris() :
		Particle3D(10.0f, 15.0f),
		moveDir(Vector3::Random()),
		initSpeed(Math::RandomRange(0.05f, 1.0f))
	{

	}

	/**************************************
	EnemySmallDebris初期化処理
	***************************************/
	void EnemySmallDebris::Init()
	{
		active = true;
		cntFrame = 0.0f;
	}

	/**************************************
	EnemySmallDebris更新処理
	***************************************/
	void EnemySmallDebris::Update()
	{
		if (!IsActive())
			return;

		cntFrame += EnemyTimeController::GetTimeScale();

		float t = cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, 1.0f, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);

		transform->Move(moveDir * initSpeed * EnemyTimeController::GetTimeScale());
	}

	/**************************************
	EnemySmallDebrisEmitterコンストラクタ
	***************************************/
	EnemySmallDebirsEmitter::EnemySmallDebirsEmitter() :
		Enemy::EnemyParticleEmitter(32, 3.0f)
	{
		particleContainer.resize(64, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnemySmallDebris();
		}
	}

}
