//=====================================
//
//EnemyBulletVanish.cpp
//機能:エネミーバレット消失エフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "EnemyBulletVanish.h"
#include "../../../Framework/Math/Easing.h"
#include "../../Controller/EnemyTimeController.h"

/**************************************
グローバル変数
***************************************/

namespace Effect::Game
{
	/**************************************
	EnemyBulletVanishControllerコンストラクタ
	***************************************/
	EnemyBulletVanishController::EnemyBulletVanishController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 0.5f, 0.5f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/EnemyBulletVanish.png");

		const unsigned MaxEmitter = 2048;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new EnemyBulletVanishEmitter();
		}
	}

	/**************************************
	EnemyBulletVanishコンストラクタ
	***************************************/
	EnemyBulletVanish::EnemyBulletVanish() :
		Particle3D(20.0f, 40.0f),
		moveDir(Vector3::Random()),
		speed(Math::RandomRange(0.05f, 1.0f)),
		initScale(Math::RandomRange(0.6f, 1.5f))
	{

	}

	/**************************************
	EnemyBulletVanish初期化処理
	***************************************/
	void EnemyBulletVanish::Init()
	{
		cntFrame = 0.0f;
		active = true;
	}

	/**************************************
	EnemyBulletVanish更新処理
	***************************************/
	void EnemyBulletVanish::Update()
	{
		if (!IsActive())
			return;

		cntFrame += EnemyTimeController::GetTimeScale();

		float t = cntFrame / lifeFrame;
		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(scale * Vector3::One);

		transform->Move(moveDir * speed * EnemyTimeController::GetTimeScale());
	}

	/**************************************
	EnemyBulletVanishEmitterコンストラクタ
	***************************************/
	EnemyBulletVanishEmitter::EnemyBulletVanishEmitter() :
		Enemy::EnemyParticleEmitter(16, 3.0f)
	{
		particleContainer.resize(16, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new EnemyBulletVanish();
		}
	}
}