//=====================================
//
// PlayerExplosion.cpp
// 機能:プレイヤー爆発エフェクト
// Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerExplosion.h"
#include "../../../Framework/Math/Easing.h"

namespace Effect::Game
{
	/**************************************
	グローバル変数
	***************************************/

	/**************************************
	PlayerExplosionControllerコンストラクタ
	***************************************/
	PlayerExplosionController::PlayerExplosionController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 2.0f, 2.0f };
		const D3DXVECTOR2 Split = { 2.0f, 2.0f };
		MakeUnitBuffer(Size, Split);

		LoadTexture("data/TEXTURE/Particle/PlayerExplosion.png");

		const unsigned MaxParticle = 256;
		const unsigned MaxEmitter = 1;
		const float EmitDuration = 5;
		const int EmitNum = 64;

		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new BaseEmitter(EmitNum, EmitDuration);
			emitter->CreateParticleContainer<PlayerExplosion>(MaxParticle);
		}
	}

	/**************************************
	PlayerExplosionコンストラクタ
	***************************************/
	PlayerExplosion::PlayerExplosion() :
		AnimationParticle3D(2.0f, 2.0f, 60.0f, 120.0f),
		moveDir(Vector3::Random()),
		speed(Math::RandomRange(0.15f, 2.2f)),
		initScale(Math::RandomRange(0.05f, 1.2f))
	{
		moveDir = Vector3::Normalize(moveDir);
	}

	/**************************************
	PlayerExplosion初期化処理
	***************************************/
	void PlayerExplosion::Init()
	{
		cntFrame = 0;
		active = true;
	}

	/**************************************
	PlayerExplosion更新処理
	***************************************/
	void PlayerExplosion::Update()
	{
		if (!IsActive())
			return;

		cntFrame += FixedTime::GetTimeScale();

		float t = cntFrame / lifeFrame;

		float currentSpeed = Easing::EaseValue(t, speed, 0.0f, EaseType::OutCubic);
		transform->Move(moveDir * currentSpeed * FixedTime::GetTimeScale());

		float scale = Easing::EaseValue(t, initScale, 0.0f, EaseType::InExpo);
		transform->SetScale(Vector3::One * scale);

		Animation(t * 15.0f);
	}
}