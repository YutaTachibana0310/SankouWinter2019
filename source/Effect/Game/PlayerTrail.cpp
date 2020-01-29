//=====================================
//
//PlayerTrail.cpp
//機能:プレイヤートレイルエフェクト
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "PlayerTrail.h"

namespace Effect::Game
{
	/**************************************
	PlayerTrailControllerコンストラクタ
	***************************************/
	PlayerTrailController::PlayerTrailController() :
		BaseParticleController(Particle_3D)
	{
		const D3DXVECTOR2 Size = { 1.0f, 1.0f };
		MakeUnitBuffer(Size);

		LoadTexture("data/TEXTURE/Particle/PlayerTrail.png");

		const unsigned MaxEmitter = 9;
		emitterContainer.resize(MaxEmitter, nullptr);
		for (auto&& emitter : emitterContainer)
		{
			emitter = new PlayerTrailEmitter();
		}
	}

	/**************************************
	PlayerTrailコンストラクタ
	***************************************/
	PlayerTrail::PlayerTrail() :
		Particle3D(3.0f, 15.0f),
		initScale(Math::RandomRange(0.3f, 1.0f))
	{

	}

	/**************************************
	PlayerTrail初期化処理
	***************************************/
	void PlayerTrail::Init()
	{
		const D3DXVECTOR3 Offset = Vector3::Random();
		const float LengthOffset = Math::RandomRange(0.0f, 1.5f);
		transform->Move(Offset * LengthOffset);

		cntFrame = 0.0f;
		active = true;
	}

	/**************************************
	PlayerTrail更新処理
	***************************************/
	void PlayerTrail::Update()
	{
		if (!IsActive())
			return;

		cntFrame += FixedTime::GetTimeScale();

		const float Speed = 0.8f;
		transform->Move(Vector3::Back * Speed * FixedTime::GetTimeScale());
	}

	/**************************************
	PlayerTrailEmitterコンストラクタ
	***************************************/
	PlayerTrailEmitter::PlayerTrailEmitter() :
		BaseEmitter(10)
	{
		const unsigned MaxParticle = 64;
		particleContainer.resize(MaxParticle, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new PlayerTrail();
			AddChild(dynamic_cast<PlayerTrail*>(particle));
		}

		Loop(true);
	}
}